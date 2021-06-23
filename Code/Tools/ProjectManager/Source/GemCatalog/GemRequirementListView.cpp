/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <GemCatalog/GemRequirementListView.h>
#include <GemCatalog/GemRequirementDelegate.h>
#include <QStandardItemModel>

namespace O3DE::ProjectManager
{
    GemRequirementListView::GemRequirementListView(QAbstractItemModel* model, QItemSelectionModel* selectionModel, QWidget* parent)
        : QListView(parent)
    {
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        setStyleSheet("background-color: #444444;");

        setModel(model);
        setSelectionModel(selectionModel);
        setItemDelegate(new GemRequirementDelegate(model, this));
    }
} // namespace O3DE::ProjectManager