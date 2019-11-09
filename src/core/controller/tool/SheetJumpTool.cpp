#include "SheetJumpTool.h"
#include "Define.h"
#include "Editor.h"
#include "FunctionBlockNode.h"
#include "Project.h"
#include "Scene.h"
#include "SheetChangeHistoryController.h"
#include <QGraphicsSceneMouseEvent>

SheetJumpTool::SheetJumpTool() : AbstractTool(TOOL_SHEET_JUMP) {
}

SheetJumpTool::~SheetJumpTool() {
}

void SheetJumpTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  FunctionBlockNode* functionBlockNode = dynamic_cast<FunctionBlockNode*>(scene->findNode(event->scenePos()));
  Project* project = Editor::getInstance()->project();
  QString sheetName = functionBlockNode->nodeType();
  project->changeActiveSheet(sheetName);
  SheetChangeHistoryController::getInstance()->add(sheetName);
}
