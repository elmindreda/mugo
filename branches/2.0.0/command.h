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
#ifndef COMMAND_H
#define COMMAND_H


#include <QUndoCommand>
#include <QString>
#include <QStandardItem>
#include "godata.h"


class QTreeView;
class QStandardItemModel;
class SgfDocument;
class BoardWidget;


/**
  add node command
*/
class AddNodeCommand : public QUndoCommand{
    Q_DECLARE_TR_FUNCTIONS(AddNodeCommand)

public:
    AddNodeCommand(SgfDocument* doc, Go::NodePtr parentNode, Go::NodePtr node, int index, QUndoCommand *parent = 0);
    virtual void redo();
    virtual void undo();

private:
    SgfDocument* document;
    Go::NodePtr parentNode;
    Go::NodePtr node;
    int index;
};

/**
  delete node command
*/
class DeleteNodeCommand : public QUndoCommand{
    Q_DECLARE_TR_FUNCTIONS(DeleteNodeCommand)

public:
    DeleteNodeCommand(SgfDocument* doc, Go::NodePtr node, bool removeChildren, QUndoCommand *parent = 0);
    virtual void redo();
    virtual void undo();

private:
    SgfDocument* document;
    Go::NodePtr parentNode;
    Go::NodePtr node;
    bool removeChildren;
    int pos;
};

/**
  set current game command
*/
class SetCurrentGameCommand : public QUndoCommand{
    Q_DECLARE_TR_FUNCTIONS(SetCurrentGameCommand)

public:
    SetCurrentGameCommand(BoardWidget* board, Go::NodePtr game, QUndoCommand *parent = 0);
    virtual void redo();
    virtual void undo();

private:
    BoardWidget* boardWidget;
    Go::NodePtr game;
    Go::NodePtr prevGame;
};

/**
  move up sgf in collection command
*/
class MoveUpInCollectionCommand : public QUndoCommand{
    Q_DECLARE_TR_FUNCTIONS(MoveUpInCollectionCommand)

public:
    MoveUpInCollectionCommand(SgfDocument* doc, QTreeView* view, int row, QUndoCommand *parent = 0);
    virtual void redo();
    virtual void undo();

private:
    SgfDocument* document;
    QTreeView* view;
    int row;
    Go::NodePtr game;
    bool moved;
};

/**
  move down sgf in collection command
*/
class MoveDownInCollectionCommand : public QUndoCommand{
    Q_DECLARE_TR_FUNCTIONS(MoveDownInCollectionCommand)

public:
    MoveDownInCollectionCommand(SgfDocument* doc, QTreeView* view, int row, QUndoCommand *parent = 0);
    virtual void redo();
    virtual void undo();

private:
    SgfDocument* document;
    QTreeView* view;
    int row;
    Go::NodePtr game;
    bool moved;
};

/**
  delete sgf from collection command
*/
class DeleteGameFromCollectionCommand : public QUndoCommand{
    Q_DECLARE_TR_FUNCTIONS(DeleteGameInCollectionCommand)

public:
    DeleteGameFromCollectionCommand(SgfDocument* doc, QStandardItemModel* model, int row, QUndoCommand *parent = 0);
    virtual void redo();
    virtual void undo();

private:
    SgfDocument* document;
    QStandardItemModel* model;
    int row;
    Go::NodePtr game;
    bool removed;
    QList<QStandardItem*> items;
    Go::NodeList::iterator iterator;
};

/**
  set comment command
*/
class SetCommentCommand : public QUndoCommand{
    Q_DECLARE_TR_FUNCTIONS(SetCommentCommand)

public:
    SetCommentCommand(SgfDocument* doc, Go::NodePtr node, const QString& comment, QUndoCommand *parent = 0);
    virtual void redo();
    virtual void undo();

    void setComment(const QString& comment);
    Go::NodePtr getNode(){ return node; }

private:
    SgfDocument* document;
    Go::NodePtr  node;
    QString      comment;
    QString      oldComment;
};


#endif // COMMAND_H