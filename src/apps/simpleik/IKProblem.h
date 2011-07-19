#ifndef PROBLEM_H
#define PROBLEM_H

#include "optimizer/Problem.h"

namespace model3d {
    class Skeleton;
    template<class SkeletonType>
    class FileInfoSkel;
} // namespace model3d

namespace optimizer {
    class IKProblem : public optimizer::Problem {
    public:
        IKProblem();
        virtual ~IKProblem();
    
        void initProblem();
        virtual void update(double* coefs);
        model3d::Skeleton* getSkel() const;
    protected:
        model3d::FileInfoSkel<model3d::Skeleton>* mFileInfoSkel;
    };
} // namespace optimizer

#endif
