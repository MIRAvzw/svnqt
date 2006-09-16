// -*- Mode: C++; -*-
#ifndef _smart_pointer_hpp
#define _smart_pointer_hpp

#if defined  QT_THREAD_SUPPORT
#include "qmutex.h"
#endif

#include "svnqt/svnqt_defines.hpp"

/*!
 * \file smart_pointer.h
 * \brief smart pointer and reference counter
 * \author Rajko Albrecht
 *
 */

namespace svn
{

//! simple reference counter class
class ref_count {
protected:
    //! reference count member
    long m_RefCount;
#ifdef QT_THREAD_SUPPORT
    QMutex m_RefcountMutex;
#endif
public:
    //! first reference must be added after "new" via Pointer()
    ref_count() : m_RefCount(0)
#ifdef QT_THREAD_SUPPORT
                  ,m_RefcountMutex()
#endif
    {}
    virtual ~ref_count() {}
    //! add a reference
    void Incr() {
#ifdef QT_THREAD_SUPPORT
        QMutexLocker a(&m_RefcountMutex);
#endif
        ++m_RefCount;
    }
    //! delete a reference
    bool Decr() {
#ifdef QT_THREAD_SUPPORT
        QMutexLocker a(&m_RefcountMutex);
#endif
        --m_RefCount;
        return Shared();
    }
    //! is it referenced
    bool Shared() { return (m_RefCount > 0); }
};

//! reference counting wrapper class
template<class T> class smart_pointer {
    //! pointer to object
    /*!
     * this object must contain Incr(), Decr() and Shared()
     * methode as public members. The best way is, that it will be a child
     * class of RefCount
     */
    T *ptr;
public:
    //! standart constructor
    smart_pointer() { ptr = 0; }
    //! standart destructor
    /*!
     * release the reference, if it were the last reference, destroys
     * ptr
     */
    ~smart_pointer()
    {
        if (ptr && !ptr->Decr()) {
            delete ptr;
        }
    }
    //! construction
    smart_pointer(T* t) { if ( (ptr = t) ) ptr->Incr(); }
    //! Pointer copy
    smart_pointer(const smart_pointer<T>& p)
    { if ( (ptr = p.ptr) ) ptr->Incr(); }
    //! pointer copy by assignment
    smart_pointer<T>& operator= (const smart_pointer<T>& p)
    {
        // already same: nothing to do
        if (ptr == p.ptr) return *this;
        // decouple reference
        if ( ptr && !ptr->Decr()) delete ptr;
        // establish new reference
        if ( (ptr = p.ptr) ) ptr->Incr();
        return *this;
    }
    smart_pointer<T>& operator= (T*p)
    {
        if (ptr==p)return *this;
        if (ptr && !ptr->Decr()) delete ptr;
        if ( (ptr=p) ) ptr->Incr();
        return *this;
    }

    //! cast to conventional pointer
    operator T* () const { return ptr; }

    //! deref: fails for 0 pointer
    T& operator* () {return *ptr; }
    //! deref: fails for 0 pointer
    const T& operator* ()const {return *ptr; }

    //! deref with method call
    T* operator-> () {return ptr; }
    //! deref with const method call
    const T* operator-> ()const {return ptr; }

    //! supports "if (pointer)"
    operator bool () const { return (ptr != 0); }
    //! "if (pointer)" as non const
    operator bool () { return ptr != 0;}

    //! support if (!pointer)"
    bool operator! () const { return (ptr == 0); }
    //! support if (!pointer)" as non const
    bool operator! () { return (ptr == 0); }
};

} // namespace svn
#endif
