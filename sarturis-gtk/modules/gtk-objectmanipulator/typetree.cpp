/*******************************************************************************
 *
 * Sarturis is (C) Copyright 2006-2011 by Dresden University of Technology
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 * 
 ******************************************************************************/


#include "sarturis/base/stringparser.h"
#include "include/typetree.h"
using namespace sarturis::gtk;


/******************************************************************************/
TypeTree::TypeTree(SelectionHandler& H):handler(H)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
TypeTree::~TypeTree()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* TypeTree::setup()
/******************************************************************************/
{
  // Baum und Datenmodell
  tree=gtk_tree_view_new();
  treestore=gtk_tree_store_new(2,G_TYPE_STRING,G_TYPE_BOOLEAN);
  gtk_tree_view_set_model(GTK_TREE_VIEW(tree),GTK_TREE_MODEL(treestore));
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree),false);
  gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(tree),true);

  // Textrenderer und Spalte fuer Name
  GtkCellRenderer* tr=gtk_cell_renderer_text_new();
  GtkTreeViewColumn* c1=
    gtk_tree_view_column_new_with_attributes("",tr,"text",0,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tree),c1);
  
  // Checkbox-Renderer und Spalte fuer Checkbox
  GtkCellRenderer* cr=gtk_cell_renderer_toggle_new();
  g_signal_connect(cr,"toggled",(GCallback)toggle,this);
  gtk_cell_renderer_toggle_set_activatable(GTK_CELL_RENDERER_TOGGLE(cr),TRUE);
  GtkTreeViewColumn* c2=
    gtk_tree_view_column_new_with_attributes("",cr,"active",1,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tree),c2);

  // ScrolledWindow, Anzeigen und return
  GtkWidget* w=gtk_scrolled_window_new(NULL,NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(w),GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(w),tree);
  gtk_widget_show(tree);
  gtk_widget_show(w);
  return w;
}
/******************************************************************************/


/******************************************************************************/
void TypeTree::Add(const std::string& T)
/******************************************************************************/
{
  // Initialisieren
  std::string look;
  GtkTreeIter newitem;
  GtkTreeIter root;

  // Typnamen auseinandernehmen (Trenner "__"), Knoten pro Namespace/Typ
  const std::vector<std::string> tv=StringParser::Tokenizer(T,"__");
  for (unsigned int i=0;i<tv.size();++i)
  {
    // Name nachdem in type_map gesucht wird (wachsen lassen)
    if (i) look+="__";
    look+=tv[i];

    // Evtl. Baumeintrag schon da, wenn nicht -> anlegen  
    type_map::const_iterator iter=types.find(look);
    if (iter==types.end())
    {
      // anlegen (wenn i=0, dann oberster Namespace -> Wurzelknoten)
      gtk_tree_store_append(treestore,&newitem,i==0 ? NULL : &root);
      gtk_tree_store_set(treestore,&newitem,0,tv[i].c_str(),1,TRUE,-1);

      // merken
      types[look]=newitem;
      root=newitem;
    }
    else root=iter->second;  // uebernehmen
  }
}
/******************************************************************************/


/******************************************************************************/
bool TypeTree::Active(const std::string& T)
/******************************************************************************/
{
  // Suchen
  type_map::iterator iter=types.find(T);
  if (iter==types.end()) return false;

  // Wert lesen und return
  gboolean val;
  gtk_tree_model_get(GTK_TREE_MODEL(treestore),&(iter->second),1,&val,-1);
  return val ? true : false;
}
/******************************************************************************/


/******************************************************************************/
void TypeTree::set_active(GtkTreeIter iter, gboolean value)
/******************************************************************************/
{
  // Kinder
  const int nc=gtk_tree_model_iter_n_children(GTK_TREE_MODEL(treestore),&iter);
  for (int i=0;i<nc;++i)
  {
    GtkTreeIter child;
    gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(treestore),&child,&iter,i);
    set_active(child,value);
  }

  // Selber
  gtk_tree_store_set(treestore,&iter,1,value,-1);
}
/******************************************************************************/


/******************************************************************************/
void TypeTree::toggle(GtkCellRendererToggle* cell_renderer, gchar* path,
                      TypeTree* t)
/******************************************************************************/
{
  // Baumeintrag
  GtkTreeIter iter;
  if (gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(t->treestore),&iter,
                                          path)==false) return;

  // Wert rekursiv umkehren
  gboolean val;
  gtk_tree_model_get(GTK_TREE_MODEL(t->treestore),&iter,1,&val,-1);
  t->set_active(iter,!val);

  // Handler drannehmen
  t->handler.Change();
}
/******************************************************************************/
