#include <QWidget>
#include "audioscriptui_p.h"


namespace AS {
namespace detail {

Property::Property()
    : m_widget(Q_NULLPTR), m_type(detail::Property::Int)
{
}

Property::Property(Get<double>::MemFun get, Set<double>::MemFun set, QString name)
    : m_type(Property::Double),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

Property::Property(Get<float>::MemFun get, Set<float>::MemFun set, QString name)
    : m_type(Property::Float),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

Property::Property(Get<bool>::MemFun get, Set<bool>::MemFun set, QString name)
    : m_type(Property::Bool),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

Property::Property(Get<int>::MemFun get, Set<int>::MemFun set, QString name)
    : m_type(Property::Int),
      m_get(reinterpret_cast<decltype(m_get)>(get)),
      m_set(reinterpret_cast<decltype(m_set)>(set))
{

}

Property::MemberType Property::type() const
{
    return m_type;
}

bool Property::operator==(const Property& rhs) const
{
    return m_type == rhs.m_type && m_get == rhs.m_get && m_set == rhs.m_set;
}

} // detail
} // AS
