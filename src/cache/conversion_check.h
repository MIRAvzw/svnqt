/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
/*
 *  Ideas, algorithm and code taken from KDE libraries
 */

#ifndef CONVERSION_CHECK_H
#define CONVERSION_CHECK_H

#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtCore/QDate>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QRect>
#include <QtCore/QVariant>

namespace svn {
namespace ConversionCheck {

// used to distinguish between supported/unsupported types
struct supported { };
struct unsupported { };

// traits type class to define support for constraints
template <typename T>
struct QVconvertible
{
  typedef unsupported toQString;
  typedef unsupported toQVariant;
};

// constraint classes
template <typename T>
struct type_toQString
{
  void constraint() { supported x = y; }
  typename QVconvertible<T>::toQString y;
};

template <typename T>
struct type_toQVariant
{
  void constraint() { supported x = y; }
  typename QVconvertible<T>::toQVariant y;
};


// check if T is convertible to QString thru QVariant
// if not supported can't be used in QList<T> functions
template <typename T>
inline void to_QString()
{
  void (type_toQString<T>::*x)() = &type_toQString<T>::constraint;
  Q_UNUSED(x);
}

// check if T is convertible to QVariant & supported in readEntry/writeEntry
template <typename T>
inline void to_QVariant()
{
  void (type_toQVariant<T>::*x)() = &type_toQVariant<T>::constraint;
  Q_UNUSED(x);
}

// define for all types handled in readEntry/writeEntry
// string_support - is supported by QVariant(type).toString(),
//                  can be used in QList<T> functions
// variant_support - has a QVariant constructor
#define QVConversions(type, string_support, variant_support) \
template <> struct QVconvertible<type> {\
 typedef string_support toQString;\
 typedef variant_support toQVariant;\
}

// The only types needed here are the types handled in readEntry/writeEntry
// the default QVconvertible will take care of the rest.
QVConversions(bool, supported, supported);
QVConversions(int, supported, supported);
QVConversions(unsigned int, supported, supported);
QVConversions(long long, supported, supported);
QVConversions(unsigned long long, supported, supported);
QVConversions(float, supported, supported);
QVConversions(double, supported, supported);
QVConversions(QString, supported, supported);
QVConversions(QColor, unsupported, supported);
QVConversions(QFont, supported, supported);
QVConversions(QDateTime, unsupported, supported);
QVConversions(QDate, unsupported, supported);
QVConversions(QSize, unsupported, supported);
QVConversions(QRect, unsupported, supported);
QVConversions(QPoint, unsupported, supported);
QVConversions(QSizeF, unsupported, supported);
QVConversions(QRectF, unsupported, supported);
QVConversions(QPointF, unsupported, supported);
QVConversions(QByteArray, supported, supported);
QVConversions(QStringList, unsupported, supported);
QVConversions(QVariantList, unsupported, supported);
}
}

#endif

