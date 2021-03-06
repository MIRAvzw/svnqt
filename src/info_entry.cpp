/*
 * Copyright (c) 2002-2005 The RapidSvn Group.
 * Copyright (c) 2005-2009 by Rajko Albrecht (ral@alwins-world.de)
 * Copyright (c) 2011 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program (in the file LGPL.txt); if not,
 * write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA 02110-1301 USA
 */
 
#include "info_entry.h"
#include "pool.h"
#include <subversion-1/svn_client.h>
#include <subversion-1/svn_path.h>

namespace svn
{

  InfoEntry::InfoEntry()
  {
    init();
  }

  InfoEntry::InfoEntry(const svn_info_t*info,const char*path)
  {
    init(info,path);
  }

  InfoEntry::InfoEntry(const svn_info_t*info,const QString&path)
  {
    init(info,path);
  }

  InfoEntry::~InfoEntry()
  {
  }

  DateTime InfoEntry::cmtDate()const
  {
      return m_last_changed_date;
  }
  DateTime InfoEntry::textTime()const
  {
      return m_text_time;
  }
  DateTime InfoEntry::propTime()const
  {
      return m_prop_time;
  }
  bool InfoEntry::hasWc()const
  {
      return m_hasWc;
  }
  const LockEntry&InfoEntry::lockEntry()const
  {
      return m_Lock;
  }
  const QString&InfoEntry::cmtAuthor () const
  {
      return m_last_author;
  }
  const QString&InfoEntry::Name()const
  {
      return m_name;
  }
  const QString& InfoEntry::checksum()const
  {
      return m_checksum;
  }
  const QString& InfoEntry::conflictNew()const
  {
      return m_conflict_new;
  }
  const QString& InfoEntry::conflictOld()const
  {
      return m_conflict_old;
  }
  const QString& InfoEntry::conflictWrk()const
  {
      return m_conflict_wrk;
  }
  const QString& InfoEntry::copyfromUrl()const
  {
      return m_copyfrom_url;
  }
  const QString& InfoEntry::prejfile()const
  {
      return m_prejfile;
  }
  const QString& InfoEntry::reposRoot()const
  {
      return m_repos_root;
  }
  const QString& InfoEntry::url()const
  {
      return m_url;
  }
  const QString& InfoEntry::uuid()const
  {
      return m_UUID;
  }
  svn_node_kind_t InfoEntry::kind()const
  {
      return m_kind;
  }
  const Revision& InfoEntry::cmtRev()const
  {
      return m_last_changed_rev;
  }
  const Revision& InfoEntry::copyfromRev()const
  {
      return m_copy_from_rev;
  }
  const Revision& InfoEntry::revision()const
  {
      return m_revision;
  }
  svn_wc_schedule_t InfoEntry::Schedule()const
  {
      return m_schedule;
  }
  const QString&InfoEntry::prettyUrl()const
  {
      return m_pUrl;
  }
  bool InfoEntry::isDir()const
  {
      return kind()==svn_node_dir;
  }
  const QByteArray&InfoEntry::changeList()const
  {
      return m_changeList;
  }
  qlonglong InfoEntry::size()const
  {
      return m_size;
  }
  qlonglong InfoEntry::working_size()const
  {
      return m_working_size;
  }
  svn::Depth InfoEntry::depth()const
  {
      return m_depth;
  }
}

/*!
    \fn svn::InfoEntry::init()
 */
void svn::InfoEntry::init()
{
  m_name = "";
  m_last_changed_date=0;
  m_text_time = 0;
  m_prop_time = 0;
  m_hasWc = false;
  m_Lock = LockEntry();
  m_checksum = "";
  m_conflict_new = "";
  m_conflict_old = "";
  m_conflict_wrk = "";
  m_copyfrom_url = "";
  m_last_author = "";
  m_prejfile = "";
  m_repos_root = "";
  m_url = "";
  m_pUrl = "";
  m_UUID = "";
  m_kind = svn_node_none;
  m_copy_from_rev = SVN_INVALID_REVNUM;
  m_last_changed_rev = SVN_INVALID_REVNUM;
  m_revision = SVN_INVALID_REVNUM;
  m_schedule = svn_wc_schedule_normal;

  m_size = m_working_size = SVNQT_SIZE_UNKNOWN;
  m_changeList=QByteArray();
  m_depth = DepthUnknown;
}

void svn::InfoEntry::init(const svn_info_t*item,const char*path)
{
    init(item,QString::fromUtf8(path));
}

/*!
    \fn svn::InfoEntry::init(const svn_info_t*)
 */
void svn::InfoEntry::init(const svn_info_t*item,const QString&path)
{
  if (!item) {
    init();
    return;
  }
  m_name = path;
  m_last_changed_date=item->last_changed_date;
  m_text_time = item->text_time;
  m_prop_time = item->prop_time;
  if (item->lock) {
    m_Lock.init(item->lock);
  } else {
    m_Lock = LockEntry();
  }
  m_checksum = QString::fromUtf8(item->checksum);
  m_conflict_new = QString::fromUtf8(item->conflict_new);
  m_conflict_old = QString::fromUtf8(item->conflict_old);
  m_conflict_wrk = QString::fromUtf8(item->conflict_wrk);
  m_copyfrom_url = QString::fromUtf8(item->copyfrom_url);
  m_last_author = QString::fromUtf8(item->last_changed_author);
  m_prejfile = QString::fromUtf8(item->prejfile);
  m_repos_root = QString::fromUtf8(item->repos_root_URL);
  m_url = QString::fromUtf8(item->URL);
  m_pUrl = prettyUrl(item->URL);
  m_UUID = QString::fromUtf8(item->repos_UUID);
  m_kind = item->kind;
  m_copy_from_rev = item->copyfrom_rev;
  m_last_changed_rev = item->last_changed_rev;
  m_revision = item->rev;
  m_hasWc = item->has_wc_info;
  m_schedule = item->schedule;

#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 6)) || (SVN_VER_MAJOR > 1)
  m_size = item->size64!=SVN_INVALID_FILESIZE?qlonglong(item->size64):SVNQT_SIZE_UNKNOWN;
  m_working_size = item->working_size64!=SVN_INVALID_FILESIZE?qlonglong(item->working_size64):SVNQT_SIZE_UNKNOWN;
  if (m_working_size == SVNQT_SIZE_UNKNOWN) {
      m_working_size = item->working_size!=SVN_INFO_SIZE_UNKNOWN?qlonglong(item->working_size):SVNQT_SIZE_UNKNOWN;
  }
#elif (SVN_VER_MINOR == 5)
  m_size = item->size!=SVN_INFO_SIZE_UNKNOWN?qlonglong(item->size):SVNQT_SIZE_UNKNOWN;
  m_working_size = item->working_size!=SVN_INFO_SIZE_UNKNOWN?qlonglong(item->working_size):SVNQT_SIZE_UNKNOWN;
#endif

#if ((SVN_VER_MAJOR == 1) && (SVN_VER_MINOR >= 5)) || (SVN_VER_MAJOR > 1)
  if (item->changelist) {
      m_changeList = QByteArray(item->changelist,strlen(item->changelist));
  } else {
      m_changeList=QByteArray();
  }

  switch (item->depth) {
      case svn_depth_exclude:
          m_depth=DepthExclude;
          break;
      case svn_depth_empty:
          m_depth=DepthEmpty;
          break;
      case svn_depth_files:
          m_depth=DepthFiles;
          break;
      case svn_depth_immediates:
          m_depth=DepthImmediates;
          break;
      case svn_depth_infinity:
          m_depth=DepthInfinity;
          break;
      case svn_depth_unknown:
      default:
          m_depth=DepthUnknown;
          break;
  }
#else
  m_size = SVNQT_SIZE_UNKNOWN;
  m_working_size = SVNQT_SIZE_UNKNOWN;
  m_changeList=QByteArray();
  m_depth = DepthUnknown;
#endif
}

QString svn::InfoEntry::prettyUrl(const char*_url)const
{
    if (_url) {
        Pool pool;
        _url = svn_path_uri_decode(_url,pool);
        return QString::fromUtf8(_url);
    }
    return QString::fromUtf8("");
}

svn::InfoEntry::InfoEntry(const InfoEntry&other)
{
    m_name = other.m_name;
    m_last_changed_date=other.m_last_changed_date;
    m_text_time = other.m_text_time;
    m_prop_time = other.m_prop_time;
    m_Lock = other.m_Lock;
    m_checksum = other.m_checksum;
    m_conflict_new = other.m_conflict_new;
    m_conflict_old = other.m_conflict_old;
    m_conflict_wrk = other.m_conflict_wrk;
    m_copyfrom_url = other.m_copyfrom_url;
    m_last_author = other.m_last_author;
    m_prejfile = other.m_prejfile;
    m_repos_root = other.m_repos_root;
    m_url = other.m_url;
    m_pUrl = other.m_pUrl;
    m_UUID = other.m_UUID;
    m_kind = other.m_kind;
    m_copy_from_rev = other.m_copy_from_rev;
    m_last_changed_rev = other.m_last_changed_rev;
    m_revision = other.m_revision;
    m_hasWc = other.m_hasWc;
    m_schedule = other.m_schedule;
    m_size = other.m_size;
    m_working_size = other.m_working_size;

}
