/*
  RTQL8, Copyright (c) 2011 Georgia Tech Graphics Lab
  All rights reserved.

  Author	Sehoon Ha
  Date		06/12/2011
*/

#include "Skeleton.h"

#include <cassert>
using namespace std;
using namespace Eigen;

#include "Dof.h"
#include "Joint.h"
#include "BodyNode.h"
#include "Marker.h"
#include "Transformation.h"

#include "renderer/RenderInterface.h"


namespace model3d {

    Skeleton::Skeleton() {
        mMass = 0;
    }

    Skeleton::~Skeleton(){
        for(unsigned int i = 0; i < mJoints.size(); i++) delete mJoints[i];
        mJoints.clear();
        mDofs.clear();
        mTransforms.clear();
        for(unsigned int i=0; i<mNodes.size(); i++) delete mNodes[i];
        mNodes.clear();
        mHandles.clear();
    }

    void Skeleton::addHandle(Marker *_h) {
        mHandles.push_back(_h);
        _h->setModelIndex(mHandles.size()-1);
        BodyNode *body = _h->getNode();
        body->addHandle(_h);
    }

    void Skeleton::addNode(BodyNode *b) {
        mNodes.push_back(b);
        b->setModelIndex(mNodes.size()-1);
        addJoint(b->getJointIn());
    }

    void Skeleton::addJoint(Joint *_j) {
        mJoints.push_back(_j);
        _j->setModelIndex(mJoints.size()-1);
    }

    void Skeleton::addDof(Dof *q) {
        mDofs.push_back(q);
        q->setModelIndex(mDofs.size()-1);
        q->setVariable();
    }

    void Skeleton::addTransform(Transformation *t) {
        mTransforms.push_back(t);
        t->setVariable(true);
        t->setModelIndex(mTransforms.size()-1);
        for(int i=0; i<t->getNumDofs(); i++) {
            addDof(t->getDof(i));
        }
    }
  
    void Skeleton::initSkel() {
        mRoot = mNodes[0];
        nDofs = mDofs.size();
        nNodes = mNodes.size();
        nHandles = mHandles.size();

        // calculate mass
        // init the dependsOnDof stucture for each bodylink
        for(int i=0; i<nNodes; i++) {
            mNodes[i]->setModel(this);
            // mNodes[i]->setDependDofMap(nDofs);
            mNodes[i]->setDependDofList();
            mNodes.at(i)->init();
            mMass += mNodes[i]->getMass();
        }

        mCurrState = VectorXd::Zero(nDofs);

        for(int i=0; i<nDofs; i++)
            mCurrState[i] = mDofs.at(i)->getValue();
        for(int i=0; i<nNodes; i++)
            mNodes.at(i)->updateTransform();
    }

    BodyNode* Skeleton::getNode(const char* const name) {
        const int nNodes = getNumNodes();
        for(int i = 0; i < nNodes; i++){
            BodyNode* node = getNode(i);
            if (strcmp(name, node->getName()) == 0) {
                return node;
            }
        }
        return NULL;
    }

    int Skeleton::getNodeIndex(const char* const name) {
        const int nNodes = getNumNodes();
        for(int i = 0; i < nNodes; i++){
            BodyNode* node = getNode(i);
            if (strcmp(name, node->getName()) == 0) {
                return i;
            }
        }
        return -1;
    }
  
    void Skeleton::setState(const VectorXd& state, bool bCalcTrans, bool bCalcDeriv) {
        assert(state.size() == nDofs);
        int k=0;
        for(k=0; k<nDofs; k++)
            if(mCurrState[k]!=state[k]) break;
        if(k==nDofs) return;

        mCurrState = state;
        for(int i=0; i<nDofs; i++) {
            mDofs.at(i)->setValue(state[i]);
        }

        if (bCalcTrans) {
            for(int i = 0; i < nNodes; i++) {
                mNodes.at(i)->updateTransform();
            }
        }

        if (bCalcDeriv) {
            for(int i = 0; i < nNodes; i++) {
                mNodes.at(i)->updateDerivatives();
            }
        }
    }

    void Skeleton::setState(const vector<double>& state, bool bCalcTrans, bool bCalcDeriv) {
        VectorXd x(state.size());
        for (int i = 0; i < state.size(); i++) {
            x(i) = state[i];
        }
        setState(x, bCalcTrans, bCalcDeriv);
    }

    void Skeleton::setPose(const VectorXd& _pose){
#ifdef DEBUG
        assert(_pose.size() == nDofs);
#endif
        for(int i=0; i<nDofs; i++)
            mDofs[i]->setValue(_pose(i));
    }

    void Skeleton::setPose(const vector<double>& _pose){
#ifdef DEBUG
        assert(_pose.size() == nDofs);
#endif
        for(int i=0; i<nDofs; i++)
            mDofs[i]->setValue(_pose[i]);
    }

    void Skeleton::getPose(Eigen::VectorXd& _pose) {
        _pose.resize(nDofs);
        for (int i = 0; i < nDofs; i++) {
            _pose(i) = mDofs[i]->getValue();
        }
    }
    void Skeleton::getPose(std::vector<double>& _pose) {
        _pose.resize(nDofs);
        for (int i = 0; i < nDofs; i++) {
            _pose[i] = mDofs[i]->getValue();
        }
    }

	void Skeleton::draw(Renderer::RenderInterface* RI, const Vector4d& _color, bool _useDefaultColor) const {
        mRoot->draw(RI, _color, _useDefaultColor);
    }
    void Skeleton::drawHandles(Renderer::RenderInterface* RI, const Vector4d& _color, bool _useDefaultColor) const {
        mRoot->drawHandles(RI, _color, _useDefaultColor);
    }


} // namespace model3d
