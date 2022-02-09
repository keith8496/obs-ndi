/*
obs-ndi
Copyright (C) 2016-2018 St�phane Lepin <steph  name of author

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

#include "output-settings.h"

#include "../Config.h"
#include "../obs-ndi.h"
#include "../preview-output.h"

OutputSettings::OutputSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OutputSettings)
{
	ui->setupUi(this);
	connect(ui->buttonBox, SIGNAL(accepted()),
		this, SLOT(onFormAccepted()));

	ui->ndiVersionLabel->setText(ndiLib->version());
}

void OutputSettings::onFormAccepted() {
	Config* conf = Config::Current();

	conf->OutputEnabled = ui->mainOutputGroupBox->isChecked();
	conf->OutputName = ui->mainOutputName->text();
	conf->main_synthesise_video_timestamps = ui->main_synthesise_video_timestamps_checkbox->isChecked();
	conf->main_synthesise_audio_timestamps = ui->main_synthesise_audio_timestamps_checkbox->isChecked();
	conf->main_async_video_send = ui->main_async_video_send_checkbox->isChecked();

	conf->PreviewOutputEnabled = ui->previewOutputGroupBox->isChecked();
	conf->PreviewOutputName = ui->previewOutputName->text();

	conf->preview_synthesise_video_timestamps = ui->preview_synthesise_video_timestamps_checkbox->isChecked();
	conf->preview_synthesise_audio_timestamps = ui->preview_synthesise_audio_timestamps_checkbox->isChecked();
	conf->preview_async_video_send = ui->preview_async_video_send_checkbox->isChecked();

	conf->Save();

	if (conf->OutputEnabled) {
		if (main_output_is_running()) {
			main_output_stop();
		}
		main_output_start(ui->mainOutputName->text().toUtf8().constData());
	} else {
		main_output_stop();
	}

	if (conf->PreviewOutputEnabled) {
		if (preview_output_is_enabled()) {
			preview_output_stop();
		}
		preview_output_start(ui->previewOutputName->text().toUtf8().constData());
	}
	else {
		preview_output_stop();
	}
}

void OutputSettings::showEvent(QShowEvent* event) {
	Config* conf = Config::Current();

	ui->mainOutputGroupBox->setChecked(conf->OutputEnabled);
	ui->mainOutputName->setText(conf->OutputName);
	ui->main_synthesise_video_timestamps_checkbox->setChecked(conf->main_synthesise_video_timestamps);
	ui->main_synthesise_audio_timestamps_checkbox->setChecked(conf->main_synthesise_audio_timestamps);
	ui->main_async_video_send_checkbox->setChecked(conf->main_async_video_send);

	ui->previewOutputGroupBox->setChecked(conf->PreviewOutputEnabled);
	ui->previewOutputName->setText(conf->PreviewOutputName);
	ui->preview_synthesise_video_timestamps_checkbox->setChecked(conf->preview_synthesise_video_timestamps);
	ui->preview_synthesise_audio_timestamps_checkbox->setChecked(conf->preview_synthesise_audio_timestamps);
	ui->preview_async_video_send_checkbox->setChecked(conf->preview_async_video_send);
	conf->PreviewOutputEnabled = ui->previewOutputGroupBox->isChecked();
	conf->PreviewOutputName = ui->previewOutputName->text();
}

void OutputSettings::ToggleShowHide() {
	if (!isVisible())
		setVisible(true);
	else
		setVisible(false);
}

OutputSettings::~OutputSettings() {
	delete ui;
}
