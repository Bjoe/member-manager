#ifndef MEMBERFILTER_H_
#define MEMBERFILTER_H_

#include <QString>
#include <QStringList>

namespace membermanager
{
namespace model
{

class MemberFilter
{

public:
    void setDeleted(const bool aBoolean);

    QString getFilter() const;

private:
    QStringList columns;
};

}
}

#endif /* MEMBERFILTER_H_ */
