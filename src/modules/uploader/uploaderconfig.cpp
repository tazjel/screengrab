/***************************************************************************
 *   Copyright (C) 2009 - 2013 by Artem 'DOOMer' Galichkin                        *
 *   doomer3d@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "uploaderconfig.h"
#include "core/config.h"

#include <QtCore/QFile>

#include <QDebug>

// common defaults
const bool DEF_AUTO_COPY_RESULT_LIMK = false;

// imageshack.us defaults
const QString DEF_IMGSHK_USER = "";
const QString DEF_IMGSHK_PASS = "";
const QString DEF_DEFAULT_HOST = "ImgUr";

const QString  groupName = "imageshack.us";
QStringList UploaderConfig::_labelsList = QStringList() << "MediaCrush" << "Imgur" << "ImageShack";

UploaderConfig::UploaderConfig()
{
    QString configFile = Config::getConfigDir();
#ifdef Q_WS_X11    
    configFile += "uploader.conf";
#endif

#ifdef Q_WS_WIN
    configFile += "uploader.ini";
#endif
    _settings = new QSettings(configFile, QSettings::IniFormat);        
		
	_groupsList << "mediacru.sh" << "imgur.com" << "imageshack.us";
}

UploaderConfig::~UploaderConfig()
{
    delete _settings;
}

QStringList UploaderConfig::labelsList()
{
	return _labelsList;
}

QVariantMap UploaderConfig::loadSettings(const QByteArray& group, QVariantMap& mapValues)
{
	QVariantMap map;
	
	_settings->beginGroup(group);
	
	QVariant defValue, iterValue;
	QVariantMap::iterator iter = mapValues.begin();
	while(iter != mapValues.end())
	{
		defValue =  iter.value();
		iterValue = _settings->value(iter.key(), defValue);		
		map.insert(iter.key(), iterValue);
		++iter;		
	}
	
	_settings->endGroup();
	
	return map;
}

QVariant UploaderConfig::loadSingleParam(const QByteArray& group, const QByteArray& param)
{
	QVariant var;
	
	_settings->beginGroup(group);
	var = _settings->value(param);
	_settings->endGroup();
	
	return var;
}


void UploaderConfig::saveSettings(const QByteArray& group, QVariantMap& mapValues)
{
	_settings->beginGroup(group);

	QVariantMap::iterator iter = mapValues.begin();
	while(iter != mapValues.end())
	{
		_settings->setValue(iter.key(), iter.value());
		++iter;
	}

	_settings->endGroup();
}

void UploaderConfig::defaultSettings()
{
	_settings->beginGroup("common");
	_settings->setValue(KEY_AUTO_COPY_RESULT_LIMK, DEF_AUTO_COPY_RESULT_LIMK);
	_settings->setValue(KEY_DEFAULT_HOST, DEF_DEFAULT_HOST);
	_settings->endGroup();

	// imageshack.us settings
	_settings->beginGroup(_groupsList[1]);
	_settings->setValue(KEY_IMGSHK_USER, DEF_IMGSHK_USER);
	_settings->setValue(KEY_IMGSHK_PASS, DEF_IMGSHK_PASS);
	_settings->endGroup();
	
	// imgur.com settings
	_settings->beginGroup(_groupsList[0]);
	
	_settings->endGroup();
}

bool UploaderConfig::autoCopyResultLink()
{
	_settings->beginGroup("common");
	bool ret = _settings->value(KEY_AUTO_COPY_RESULT_LIMK, DEF_AUTO_COPY_RESULT_LIMK).toBool();
	_settings->endGroup();
	
	return ret;
}


bool UploaderConfig::checkExistsConfigFile() const
{	
	return QFile::exists(_settings->fileName());
}