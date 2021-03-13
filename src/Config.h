/*
obs-ndi
Copyright (C) 2016-2018 Stéphane Lepin <steph  name of author

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; If not, see <https://www.gnu.org/licenses/>
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QCheckBox>
#include <obs-module.h>

class Config {
  public:
	Config();
	static void OBSSaveCallback(obs_data_t* save_data,
		bool saving, void* private_data);
	static Config* Current();
	void Load();
	void Save();

	bool OutputEnabled;
	bool main_synthesise_video_timestamps;
	bool main_synthesise_audio_timestamps;
	bool main_async_video_send;
	QString OutputName;
	QCheckBox main_synthesise_video_timestamps_checkbox;
	QCheckBox main_synthesise_audio_timestamps_checkbox;
	QCheckBox main_async_video_send_checkbox;
	QString PreviewOutputName;
	QCheckBox preview_synthesise_video_timestamps_checkbox;
	QCheckBox preview_synthesise_audio_timestamps_checkbox;
	QCheckBox preview_async_video_send_checkbox;
	bool PreviewOutputEnabled;
	bool preview_synthesise_video_timestamps;
	bool preview_synthesise_audio_timestamps;
	bool preview_async_video_send;

  private:
	static Config* _instance;
};

#endif // CONFIG_H
