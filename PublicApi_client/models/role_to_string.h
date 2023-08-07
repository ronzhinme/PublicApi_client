#ifndef CLASS_ROLE_TO_STRING_CPP
#define CLASS_ROLE_TO_STRING_CPP

#include <QString>
#include <QVariantList>

namespace DataModels
{
class RoleToString final
{
public:
    static int toRoleIndex(const QString &name, const QVariantList &values, int notFoundValue)
    {
        for(auto i = 0; i < values.count(); ++i)
        {
            if(values.at(i).toString() == name)
            {
                return i;
            }
        }

        return notFoundValue;
    }

    static QString toString(int roleIndex, const QVariantList &values, const QString &notFoundValue)
    {
        if(values.empty() || roleIndex > values.count() || roleIndex < 0)
        {
            return notFoundValue;
        }

        return values.at(roleIndex).toString();
    }
};
}
#endif // CLASS_ROLE_TO_STRING_CPP
