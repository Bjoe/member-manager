#ifndef SUMMARWRITER_H_
#define SUMMARWRITER_H_

#include <QString>

namespace membermanager
{

class SummaryWriter
{
public:
    virtual ~SummaryWriter() {}

    virtual void writeContent(const QString &aContent) = 0;
};

}

#endif /* SUMMARWRITER_H_ */
