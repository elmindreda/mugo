/*
    mugo, sgf editor.
    Copyright (C) 2009-2010 nsase.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <QDebug>
#include "boardsizedialog.h"
#include "ui_boardsizedialog.h"

BoardSizeDialog::BoardSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BoardSizeDialog)
{
    ui->setupUi(this);
}

BoardSizeDialog::~BoardSizeDialog()
{
    delete ui;
}

void BoardSizeDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/**
* slot
* ok button was clicked.
*/
void BoardSizeDialog::accept()
{
    QDialog::accept();
    if (ui->radio19Button->isChecked())
        size = 19;
    else if (ui->radio13Button->isChecked())
        size = 13;
    else if (ui->radio9Button->isChecked())
        size = 9;
    else
        size = ui->customSpinBox->value();
}

/**
* slot
* custom radio button was toggled.
*/
void BoardSizeDialog::on_radioCustomButton_toggled(bool checked)
{
    // if custom radio button is checked, enable custom spin button.
    ui->customSpinBox->setEnabled(checked);
}