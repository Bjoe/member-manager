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
    static MemberFilter build();
    MemberFilter &withDeleted(const bool aBoolean);

    QString createFilter() const;

private:
    QStringList columns;

    MemberFilter();
};

}
}

#endif /* MEMBERFILTER_H_ */
