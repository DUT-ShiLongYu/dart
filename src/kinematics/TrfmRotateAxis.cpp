/*
 * Copyright (c) 2013, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Tobias Kunz <tobias@gatech.edu>
 * Date: 02/02/2013
 *
 * Geoorgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#include "TrfmRotateAxis.h"
#include "Dof.h"
#include "renderer/RenderInterface.h"

using namespace Eigen;

namespace kinematics {
    TrfmRotateAxis::TrfmRotateAxis(const Eigen::Vector3d& _axis, Dof* _angle, const char* _name) :
        mAxis(_axis)
    {
        mDofs.push_back(_angle);
        _angle->setTrans(this);
        mType = Transformation::T_ROTATEAXIS;
        if(_name!=NULL)
            strcpy(mName, _name);
        else
            strcpy(mName, "RotateAxis");
    }

    void TrfmRotateAxis::applyGLTransform(renderer::RenderInterface* _ri) const{
        if (_ri)
            _ri->rotate(mAxis, mDofs[0]->getValue() * 180.0 / M_PI);
    }

    void TrfmRotateAxis::computeTransform(){
        mTransform = ((Affine3d)AngleAxis<double>(mDofs[0]->getValue(), mAxis)).matrix();
    }

    Matrix4d TrfmRotateAxis::getDeriv(const Dof *q){
        if(q == mDofs[0])
            return ((Affine3d)AngleAxis<double>(mDofs[0]->getValue() + M_PI / 2.0, mAxis)).matrix();
        else
            return Matrix4d::Zero();
    }

    Matrix4d TrfmRotateAxis::getSecondDeriv(const Dof *q1, const Dof *q2){
        if(mDofs[0] == q1 && mDofs[0] == q2)
            return ((Affine3d)AngleAxis<double>(mDofs[0]->getValue() + M_PI, mAxis)).matrix();
        else {
            return Matrix4d::Zero();
        }
    }

    Matrix4d TrfmRotateAxis::getInvTransform(){
        return ((Affine3d)AngleAxis<double>(-mDofs[0]->getValue(), mAxis)).matrix();
    }

} // namespace kinematics
