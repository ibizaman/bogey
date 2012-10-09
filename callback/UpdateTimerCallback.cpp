#include "UpdateTimerCallback.h"

void UpdateTimerCallback::operator()(osg::Uniform* uniform, osg::NodeVisitor* nv)
{
    uniform->set((float)nv->getFrameStamp()->getSimulationTime());
}
