#ifndef UNITTESTS_TESTDYNAMICS_H
#define UNITTESTS_TESTDYNAMICS_H

#include "dynamics/BodyNodeDynamics.h"
#include "dynamics/SkeletonDynamics.h"
#include "model3d/FileInfoSkel.hpp"
#include "model3d/FileInfoDof.h"
#include "model3d/BodyNode.h"
#include "utils/Paths.h"
#include <iostream>
#include <Eigen/Dense>

dynamics::SkeletonDynamics* prepareSkeleton( Eigen::VectorXd& _q, Eigen::VectorXd& _qdot) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;

    // load skeleton
    const char* skelfilename = GROUNDZERO_DATA_PATH"skel/Yuting.vsk";
    FileInfoSkel<SkeletonDynamics>* skelFile = new FileInfoSkel<SkeletonDynamics>;
    bool loadModelResult = skelFile->loadFile(skelfilename, model3d::VSK);
    assert(loadModelResult);

    SkeletonDynamics *skelDyn = static_cast<SkeletonDynamics*>(skelFile->getSkel());
    assert(skelDyn != NULL);

    // generate a random state
    _q = VectorXd::Zero(skelDyn->getNumDofs());
    _qdot = VectorXd::Zero(skelDyn->getNumDofs());
    for(int i=0; i<skelDyn->getNumDofs(); i++){
        _q[i] = utils::random(-1.0, 1.0);
        _qdot[i] = utils::random(-5.0, 5.0);
    }

    return skelDyn;
}

void addExternalForces(dynamics::SkeletonDynamics* skelDyn) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;

    ((BodyNodeDynamics*)skelDyn->getNode(7))->addExtForce(Vector3d(0.1,0.2,0.3), Vector3d(30,40,50), true, false );
    ((BodyNodeDynamics*)skelDyn->getNode(7))->addExtForce(Vector3d(0.5,0.5,0.5), -Vector3d(20,4,5), true, false );
    ((BodyNodeDynamics*)skelDyn->getNode(13))->addExtForce(Vector3d(0,0,0), Vector3d(30,20,10), true, false );
    ((BodyNodeDynamics*)skelDyn->getNode(2))->addExtTorque(Vector3d(30,20,10), false );
}

TEST(DYNAMICS, COMPARE_VELOCITIES) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;

    const double TOLERANCE_EXACT = 1.0e-10;
    Vector3d gravity(0.0, -9.81, 0.0);
   
    VectorXd q, qdot;
    SkeletonDynamics *skelDyn = prepareSkeleton(q,qdot);
    skelDyn->setPose(q, false, false);

    // test the velocities computed by the two methods
    skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
    for(int i=0; i<skelDyn->getNumNodes(); i++){
        BodyNodeDynamics *nodei = static_cast<BodyNodeDynamics*>(skelDyn->getNode(i));
        EXPECT_TRUE(nodei != NULL);
        // compute velocities using regular method
        nodei->updateTransform();
        nodei->updateFirstDerivatives();
        nodei->evalJacLin();
        nodei->evalJacAng();
        Vector3d v1 = Vector3d::Zero();
        Vector3d w1 = Vector3d::Zero();
        for(int j=0; j<nodei->getNumDependentDofs(); j++){
            int dj = nodei->getDependentDof(j);
            for(int k=0; k<3; k++) {
                v1[k] += nodei->getJacobianLinear() (k, j)*qdot[dj];
                w1[k] += nodei->getJacobianAngular()(k, j)*qdot[dj];
            }
        }

        // compute velocities using inverse dynamics routine
        Vector3d v2 = nodei->getWorldTransform().topLeftCorner(3,3)*nodei->mVelBody;
        Vector3d w2 = nodei->getWorldTransform().topLeftCorner(3,3)*nodei->mOmegaBody;

        for(int k=0; k<3; k++) {
            EXPECT_NEAR(v1[k], v2[k], TOLERANCE_EXACT);
            EXPECT_NEAR(w1[k], w2[k], TOLERANCE_EXACT);
        }

        // Angular Jacobian regular
        MatrixXd Jw_regular = (nodei->getJacobianAngular()).rightCols(nodei->getParentJoint()->getNumDofsRot());
        // Angular jacobian inverse dynamics
        MatrixXd Jw_invdyn = nodei->mJwJoint;
        if(nodei->getParentNode()) Jw_invdyn = nodei->getParentNode()->getWorldTransform().topLeftCorner(3,3)*Jw_invdyn;
        ASSERT_TRUE(Jw_regular.rows()==Jw_invdyn.rows());
        ASSERT_TRUE(Jw_regular.cols()==Jw_invdyn.cols());
        for(int ki=0; ki<Jw_regular.rows(); ki++){
            for(int kj=0; kj<Jw_regular.cols(); kj++){
                EXPECT_NEAR(Jw_regular(ki,kj), Jw_invdyn(ki,kj), TOLERANCE_EXACT);
            }
        }
    }
}
TEST(DYNAMICS, FINITEDIFF_ACCELERATIONS_INVERSEDYNAMICS) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;
    
    Vector3d gravity(0.0, -9.81, 0.0);
    double TOLERANCE_APPROX = 1.1e-3;
    
    VectorXd q, qdot;
    SkeletonDynamics* skelDyn = prepareSkeleton(q, qdot);
    skelDyn->setPose(q, false, false);
    
    double dt = 1.0e-6;
    VectorXd origq = q;
    VectorXd newq = q + qdot*dt;
    for(int i=0; i<skelDyn->getNumNodes(); i++){
        BodyNodeDynamics *nodei = static_cast<BodyNodeDynamics*>(skelDyn->getNode(i));
        EXPECT_TRUE(nodei != NULL);

        skelDyn->setPose(origq);
        skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
        Matrix3d Ri = nodei->getWorldTransform().topLeftCorner(3,3);

        MatrixXd JwOrig = nodei->mJwJoint;
        MatrixXd JwDotOrig = nodei->mJwDotJoint;
        Vector3d wOrig = Ri*nodei->mOmegaBody;
        Vector3d wDotOrig = Ri*nodei->mOmegaDotBody;
        Vector3d vOrig = Ri*nodei->mVelBody;
        Vector3d vDotOrig = Ri*nodei->mVelDotBody + gravity;

        skelDyn->setPose(newq);
        skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
        Matrix3d Rinew = nodei->getWorldTransform().topLeftCorner(3,3);

        MatrixXd JwNew = nodei->mJwJoint;
        MatrixXd JwDotApprox = (JwNew-JwOrig)/dt;
        Vector3d wNew = Rinew*nodei->mOmegaBody;
        Vector3d wDotApprox = (wNew-wOrig)/dt;
        Vector3d vNew = Rinew*nodei->mVelBody;
        Vector3d vDotApprox = (vNew-vOrig)/dt;

        for(int ki=0; ki<JwDotOrig.rows(); ki++){
            EXPECT_NEAR(vDotOrig[ki], vDotApprox[ki], TOLERANCE_APPROX);
            EXPECT_NEAR(wDotOrig[ki], wDotApprox[ki], TOLERANCE_APPROX);
            for(int kj=0; kj<JwDotOrig.cols(); kj++){
                EXPECT_NEAR(JwDotOrig(ki,kj), JwDotApprox(ki,kj), TOLERANCE_APPROX);
            }
        }

    }
}

TEST(DYNAMICS, COMPARE_CORIOLIS) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;

    const double TOLERANCE_EXACT = 1.0e-10;
    Vector3d gravity(0.0, -9.81, 0.0);

    VectorXd q, qdot;
    SkeletonDynamics* skelDyn = prepareSkeleton(q, qdot);
    skelDyn->setPose(q, false, false);

    // test/compare the dynamics result for both methods
    VectorXd Cginvdyn = skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
    skelDyn->computeDynamics(gravity, qdot, false); // compute dynamics by not using inverse dynamics

    for(int ki=0; ki<Cginvdyn.size(); ki++){
        EXPECT_NEAR(Cginvdyn[ki], skelDyn->getCombinedVector()[ki], TOLERANCE_EXACT);
    }
}

TEST(DYNAMICS, COMPARE_MASS) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;
    
    const double TOLERANCE_EXACT = 1.0e-10;
    Vector3d gravity(0.0, -9.81, 0.0);

    VectorXd q, qdot;
    SkeletonDynamics* skelDyn = prepareSkeleton(q, qdot);
    skelDyn->setPose(q, false, false);

    // test/compare the dynamics result for both methods
    // test the mass matrix
    skelDyn->computeDynamics(gravity, qdot, true); // compute dynamics by using inverse dynamics
    MatrixXd Minvdyn( skelDyn->getMassMatrix() );
    skelDyn->computeDynamics(gravity, qdot, false); // compute dynamics by NOT using inverse dynamics: use regular dynamics
    MatrixXd Mregular( skelDyn->getMassMatrix() );

    for(int ki=0; ki<Minvdyn.rows(); ki++){
        for(int kj=0; kj<Minvdyn.cols(); kj++){
            EXPECT_NEAR(Minvdyn(ki,kj), Mregular(ki,kj), TOLERANCE_EXACT);
        }
    }
}


TEST(DYNAMICS, COMPARE_EXTERNAL_FORCES) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;

    const double TOLERANCE_EXACT = 1.0e-10;
    Vector3d gravity(0.0, -9.81, 0.0);

    VectorXd q, qdot;
    SkeletonDynamics* skelDyn = prepareSkeleton(q, qdot);
    skelDyn->setPose(q, true, true); 
    
    addExternalForces(skelDyn); // adding external force may require transformations to be computed to convert points and forces to local coordinates
    skelDyn->computeInverseDynamicsLinear(gravity, &qdot); // some computation in inverse dynamics is required even when only external forces are desired
    skelDyn->evalExternalForces(true); // use recursive
    VectorXd Frec = skelDyn->getExternalForces();
    
    skelDyn->clearExternalForces();
    addExternalForces(skelDyn);
    skelDyn->evalExternalForces(false); // use non-recursive Jacobian method; assume first derivatives are computed already
    VectorXd Fnon = skelDyn->getExternalForces();

    for(int i=0; i<skelDyn->getNumDofs(); i++)
        EXPECT_NEAR(Frec(i), Fnon(i), TOLERANCE_EXACT);
}


TEST(DYNAMICS, COMPARE_DYN_EXTERNAL_FORCES) {
    using namespace std;
    using namespace Eigen;
    using namespace model3d;
    using namespace dynamics;

    const double TOLERANCE_EXACT = 1.0e-10;
    Vector3d gravity(0.0, -9.81, 0.0);

    VectorXd q, qdot;
    SkeletonDynamics* skelDyn = prepareSkeleton(q, qdot);
    skelDyn->setPose(q, true, true); 
    
    addExternalForces(skelDyn);
    skelDyn->computeDynamics(gravity, qdot, true); // compute dynamics by using inverse dynamics
    MatrixXd MRec = skelDyn->getMassMatrix();
    VectorXd CRec = skelDyn->getCombinedVector();

    addExternalForces(skelDyn);
    skelDyn->computeDynamics(gravity, qdot, false); // compute dynamics by NOT using inverse dynamics: use regular dynamics
    MatrixXd MNon = skelDyn->getMassMatrix();
    VectorXd CNon = skelDyn->getCombinedVector();

    for(int i=0; i<skelDyn->getNumDofs(); i++)
        EXPECT_NEAR(CRec(i), CNon(i), TOLERANCE_EXACT);

    for(int i=0; i<skelDyn->getNumDofs(); i++)
        for(int j=i; j<skelDyn->getNumDofs(); j++)
            EXPECT_NEAR(MRec(i,j), MNon(i,j), TOLERANCE_EXACT);
}

// TODO
TEST(DYNAMICS, CONVERSION_VELOCITY) {
}

TEST(DYNAMICS, CONVERSION_FORCES) {
}

#endif // #ifndef UNITTESTS_TESTDYNAMICS_H

