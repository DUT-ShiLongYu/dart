/*
  RTQL8, Copyright (c) 2011 Georgia Tech Graphics Lab
  All rights reserved.

  Author	Sehoon Ha
  Date		06/12/2011
*/

#include "Joint.h"

#include "Dof.h"
#include "Transformation.h"
#include "BodyNode.h"
#include <iostream>
#include <map>
using namespace Eigen;
using namespace std;


namespace model3d {
    Joint::Joint(BodyNode *_bIn, BodyNode *_bOut, const char *_name){
		mType = J_UNKNOWN;
        mSkelIndex=-1;
        mNodeIn=_bIn;
        mNodeOut=_bOut;
        if(mNodeIn != NULL) mNodeIn->addJointOut(this);
        if(mNodeOut != NULL) mNodeOut->setJointIn(this);
        mNumDofsRot=0;
        mNumDofsTrans=0;
        mRotTransIndex.clear();
        if(_name) setName(_name);
    }

    Joint::~Joint(){
        for(unsigned int i=0; i<mTransforms.size(); i++){
            delete mTransforms[i];
        }
        mTransforms.clear();
        mDofs.clear();
    }

    bool Joint::isPresent (const Dof* _q) const{
        for(unsigned int i=0; i<mDofs.size(); i++)
            if(_q==mDofs[i]) return true;
        return false;
    }

    int Joint::getLocalIndex (int _dofSkelIndex) const{
        for(unsigned int i=0; i<mDofs.size(); i++)
            if(mDofs[i]->getSkelIndex()==_dofSkelIndex) return i;
        return -1;
    }

    Matrix4d Joint::getLocalTransform(){
        Matrix4d m = Matrix4d::Identity();
        for(int i= mTransforms.size()-1; i>=0; i--) {
            mTransforms[i]->applyTransform(m);
        }
        return m;
    }

    void Joint::applyTransform(Vector3d& _v){
        for(int i=mTransforms.size()-1; i>=0; i--){
            mTransforms[i]->applyTransform(_v);
        }
    }

    void Joint::applyTransform(Matrix4d& _m){
        for(int i=mTransforms.size()-1; i>=0; i--){
            mTransforms[i]->applyTransform(_m);
        }
    }

    void Joint::computeJac(MatrixXd *_J, MatrixXd *_Jdot, VectorXd *_qdot){
        assert(_J);
        _J->resize(3, mNumDofsRot);
        _J->setZero();
        if(_Jdot) {
            _Jdot->resize(3, mNumDofsRot);
            _Jdot->setZero();
        }

        map<Transformation::TransFormType, int> rotEulerMap;
        rotEulerMap[Transformation::T_ROTATEX]=0;
        rotEulerMap[Transformation::T_ROTATEY]=1;
        rotEulerMap[Transformation::T_ROTATEZ]=2;

        if(mType==J_HINGE){
            assert(mNumDofsRot==1);
            assert(mRotTransIndex.size()==1);
            (*_J)(rotEulerMap[mTransforms[mRotTransIndex[0]]->getType()], 0) = 1.0;
            // _Jdot is zero
        }
        else if(mType==J_UNIVERSAL){
            assert(mNumDofsRot==2);
            assert(mRotTransIndex.size()==2);

            Matrix4d R0 = mTransforms[mRotTransIndex[0]]->getTransform();
            // first col
            (*_J)(rotEulerMap[mTransforms[mRotTransIndex[0]]->getType()], 0) = 1.0;
            // second col
            for(int r=0; r<3; r++) (*_J)(r, 1) = R0(r, rotEulerMap[mTransforms[mRotTransIndex[1]]->getType()]);
            if(_Jdot){
                // first col is zero
                // second col w_0 x(R_0*e_1), (w_0 = e_0*qd_0) == qd_0 * J_0 x J_1
                Vector3d J_0((*_J)(0,0), (*_J)(1,0), (*_J)(2,0));
                Vector3d J_1((*_J)(0,1), (*_J)(1,1), (*_J)(2,1));
                Vector3d Jdot_1 = J_0.cross(J_1)*(*_qdot)[0];
                for(int r=0; r<3; r++) (*_Jdot)(r, 1) = Jdot_1[r];
            }

        }
        else if(mType==J_BALLEULER || mType==J_FREEEULER){
            assert(mNumDofsRot==3);
            assert(mRotTransIndex.size()==3);

            Matrix4d R0 = mTransforms[mRotTransIndex[0]]->getTransform();
            Matrix4d R1 = mTransforms[mRotTransIndex[1]]->getTransform();
            // first col
            (*_J)(rotEulerMap[mTransforms[mRotTransIndex[0]]->getType()], 0) = 1.0;
            // second col
            for(int r=0; r<3; r++) (*_J)(r, 1) = R0(r, rotEulerMap[mTransforms[mRotTransIndex[1]]->getType()]);
            // third col
            VectorXd R1e2 = R1.col(rotEulerMap[mTransforms[mRotTransIndex[2]]->getType()]);
            VectorXd J_2 = R0*R1e2;
            for(int r=0; r<3; r++) (*_J)(r, 2) = J_2[r];
            if(_Jdot){
                // first col is zero
                // second col w_0 x(R_0*e_1), (w_0 = e_0*qd_0) == qd_0 * J_0 x J_1
                Vector3d J_0((*_J)(0, 0), (*_J)(1, 0), (*_J)(2, 0));
                Vector3d J_1((*_J)(0, 1), (*_J)(1, 1), (*_J)(2, 1));
                Vector3d J_2((*_J)(0, 2), (*_J)(1, 2), (*_J)(2, 2));
                Vector3d Jdot_1 = J_0.cross(J_1)*(*_qdot)[0];
                Vector3d J0qd0pJ1qd1 = J_0*(*_qdot)[0] + J_1*(*_qdot)[1];
                Vector3d Jdot_2 = J0qd0pJ1qd1.cross(J_2);
                for(int r=0; r<3; r++) {
                    (*_Jdot)(r, 1) = Jdot_1[r];
                    (*_Jdot)(r, 2) = Jdot_2[r];
                }
            }
        }
        else {
            cout<<"computeJac not implemented yet for this joint type\n";
        }
    }

    utils::rot_conv::RotationOrder Joint::getEulerOrder(){
        if(mType == J_BALLEXPMAP || mType == J_FREEEXPMAP) return utils::rot_conv::UNKNOWN;

        assert(mNumDofsRot==mRotTransIndex.size());
        string rot="";
        for(int i=mNumDofsRot-1; i>=0; i--){
            if(mTransforms[mRotTransIndex[i]]->getType()==Transformation::T_ROTATEX) rot+="x";
            else if(mTransforms[mRotTransIndex[i]]->getType()==Transformation::T_ROTATEY) rot+="y";
            else if(mTransforms[mRotTransIndex[i]]->getType()==Transformation::T_ROTATEZ) rot+="z";
        }

        if(rot.compare("xyz")==0 || rot.compare("xy")==0 || rot.compare("yz")==0 || rot.compare("xz")==0 || rot.compare("x")==0 || rot.compare("y")==0 || rot.compare("z")==0) return utils::rot_conv::XYZ;
        if(rot.compare("yzx")==0 ) return utils::rot_conv::YZX;
        if(rot.compare("zxy")==0 ) return utils::rot_conv::ZXY;
        if(rot.compare("xzy")==0 ) return utils::rot_conv::XZY;
        if(rot.compare("yxz")==0 ) return utils::rot_conv::YXZ;
        if(rot.compare("zyx")==0 || rot.compare("zy")==0|| rot.compare("yx")==0|| rot.compare("zx")==0 ) return utils::rot_conv::ZYX;

        return utils::rot_conv::UNKNOWN;
    }

    Vector3d Joint::getAxis( unsigned int _i ){
        assert(_i>=0 && _i<=2);
        if(mTransforms.size()<=_i) return Vector3d::Zero();
        Transformation *rot = mTransforms[mTransforms.size()-_i - 1];
        if(rot->getType()==Transformation::T_ROTATEX) return Vector3d::UnitX();
        if(rot->getType()==Transformation::T_ROTATEY) return Vector3d::UnitY();
        if(rot->getType()==Transformation::T_ROTATEZ) return Vector3d::UnitZ();
        return Vector3d::Zero();
    }

    Matrix4d Joint::getDeriv(const Dof* _q){
        Matrix4d m = Matrix4d::Identity();
        for(int i=mTransforms.size()-1; i>=0; i--){
            if(mTransforms[i]->isPresent(_q))
                mTransforms[i]->applyDeriv(_q, m);
            else	
                mTransforms[i]->applyTransform(m);
        }
        return m;
    }

    void Joint::applyDeriv(const Dof* _q, Vector3d& _v){
        for(int i=mTransforms.size()-1; i>=0; i--){
            if(mTransforms[i]->isPresent(_q))
                mTransforms[i]->applyDeriv(_q, _v);
            else	
                mTransforms[i]->applyTransform(_v);
        }
    }

    void Joint::applyDeriv(const Dof* _q, Matrix4d& _m){
        for(int i=mTransforms.size()-1; i>=0; i--){
            if(mTransforms[i]->isPresent(_q))
                mTransforms[i]->applyDeriv(_q, _m);
            else	
                mTransforms[i]->applyTransform(_m);
        }
    }

    Matrix4d Joint::getSecondDeriv(const Dof* _q1, const Dof* _q2){
        Matrix4d m = Matrix4d::Identity();
        for(int i=mTransforms.size()-1; i>=0; i--){
            Transformation* transf = mTransforms[i];
            if(transf->isPresent(_q1) && transf->isPresent(_q2)){
                transf->applySecondDeriv(_q1, _q2, m);
            }else if(transf->isPresent(_q1)){
                transf->applyDeriv(_q1, m);
            }else if(transf->isPresent(_q2)){
                transf->applyDeriv(_q2, m);
            }else{
                transf->applyTransform(m);
            }
        }
        return m;
    }

    void Joint::applySecondDeriv(const Dof* _q1, const Dof* _q2, Vector3d& _v){
        for(int i=mTransforms.size()-1; i>=0; i--){
            Transformation* transf = mTransforms[i];
            if(transf->isPresent(_q1) && transf->isPresent(_q2)){
                transf->applySecondDeriv(_q1, _q2, _v);
            }else if(transf->isPresent(_q1)){
                transf->applyDeriv(_q1, _v);
            }else if(transf->isPresent(_q2)){
                transf->applyDeriv(_q2, _v);
            }else{
                transf->applyTransform(_v);
            }
        }
    }

    void Joint::applySecondDeriv(const Dof* _q1, const Dof* _q2, Matrix4d& _m){
        for(int i=mTransforms.size()-1; i>=0; i--){
            Transformation* transf = mTransforms[i];
            if(transf->isPresent(_q1) && transf->isPresent(_q2)){
                transf->applySecondDeriv(_q1, _q2, _m);
            }else if(transf->isPresent(_q1)){
                transf->applyDeriv(_q1, _m);
            }else if(transf->isPresent(_q2)){
                transf->applyDeriv(_q2, _m);
            }else{
                transf->applyTransform(_m);
            }
        }
    }

    void Joint::addTransform(Transformation *_t, bool _isVariable){
        _t->setJoint(this);
        _t->setVariable(_isVariable);
        mTransforms.push_back(_t);
        if(_isVariable) {	// add dofs of variable transform only
            for(int i=0; i<_t->getNumDofs(); i++){
                addDof(_t->getDof(i));
            }
            switch(_t->getType()){
            case Transformation::T_ROTATEX:
            case Transformation::T_ROTATEY:
            case Transformation::T_ROTATEZ:
            case Transformation::T_ROTATEEXPMAP:
                mNumDofsRot+=_t->getNumDofs();
                mRotTransIndex.push_back(mTransforms.size()-1);
                break;
            default:	// translation dofs
                mNumDofsTrans+=_t->getNumDofs();
                break;
            }
            if(_t->getType()==Transformation::T_ROTATEEXPMAP && mNumDofsRot==3 && mNumDofsTrans==3) mType=J_FREEEXPMAP;
            else if(_t->getType()==Transformation::T_ROTATEEXPMAP && mNumDofsRot==3 && mNumDofsTrans==0) mType=J_BALLEXPMAP;
            else if(mNumDofsRot==3 && mNumDofsTrans==3) mType=J_FREEEULER;
            else if(mNumDofsRot==3 && mNumDofsTrans==0) mType=J_BALLEULER;
            else if(mNumDofsRot==2 && mNumDofsTrans==0) mType=J_UNIVERSAL;
            else if(mNumDofsRot==1 && mNumDofsTrans==0) mType=J_HINGE;
            else if(mNumDofsRot==0 && mNumDofsTrans>0) mType=J_TRANS;
            else {
                cout<<"Joint constructed not recognized\n";
            }
        }
    }

    void Joint::addDof(Dof *_d) {
        mDofs.push_back(_d);
        _d->setJoint(this);
    }


} // namespace model3d

