#include "stdafx.h"

namespace local {

 wxBEGIN_EVENT_TABLE(TreeCtrlMain, wxTreeCtrl)
  wxEND_EVENT_TABLE()

 TreeCtrlMain::TreeCtrlMain(wxWindow* parent,
  wxWindowID id,
  const wxPoint& pos,
  const wxSize& size,
  long style,
  const wxValidator& validator,
  const wxString& name) :
  wxTreeCtrl(parent, id, pos, size, style, validator, name) {

  wxTreeItemId root = AddRoot("Project configure", 0);
  wxArrayTreeItemIds items;

  items.Add(AppendItem(root, "Item 1", 0));
  items.Add(AppendItem(root, "Item 2", 0));
  items.Add(AppendItem(root, "Item 3", 0));
  items.Add(AppendItem(root, "Item 4", 0));
  items.Add(AppendItem(root, "Item 5", 0));

  int i, count;
  for (i = 0, count = items.Count(); i < count; ++i)
  {
   wxTreeItemId id = items.Item(i);
   AppendItem(id, "Subitem 1", 1);
   AppendItem(id, "Subitem 2", 1);
   AppendItem(id, "Subitem 3", 1);
   AppendItem(id, "Subitem 4", 1);
   AppendItem(id, "Subitem 5", 1);
 }
#if 0
  const wxTreeItemId root = GetRootItem();
  const wxTreeItemId node_id_dev = AppendItem(root, "开发配置");
  AppendItem(node_id_dev, "主进程");
  AppendItem(node_id_dev, "渲染进程");
  AppendItem(node_id_dev, "网络进程");
  AppendItem(node_id_dev, "插件进程");
  AppendItem(node_id_dev, "GPU进程");

  ExpandAll();
#endif
  Expand(root);
  Refresh();
 }
 TreeCtrlMain::~TreeCtrlMain() {
 }

}///namespace local