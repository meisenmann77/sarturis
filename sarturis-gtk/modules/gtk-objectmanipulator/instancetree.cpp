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


#ifdef WIN32
  #include <shlwapi.h>
  #define MATCH(P,N) (PathMatchSpec(N,P)==TRUE)
#else
  #include <fnmatch.h>
  #define MATCH(P,N) (fnmatch(P,N,0)==0)
#endif

#include "sarturis/apps/datamanager.h"
#include "include/instancetree.h"
using namespace sarturis;
using namespace sarturis::gtk;
using namespace sarturis::reflection;


/******************************************************************************/
InstanceTree::InstanceTree():namefilter("*"),lock(new Mutex)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
InstanceTree::~InstanceTree()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void InstanceTree::Add(sarturis::ref<Type> T, sarturis::ref<Referenced> R)
/******************************************************************************/
{
  // Namen
  const std::string name=DataManager::GetName(&(*R));

  // Eintrag fuer Objekt
  GtkTreeIter iter;
  gtk_tree_store_append(treestore,&iter,NULL);
  gtk_tree_store_set(treestore,&iter,0,name.c_str(),-1);
  gtk_tree_store_set(treestore,&iter,4,T->GetName().c_str(),-1);
  attribute_tree(iter,&(*R),T);
}
/******************************************************************************/


/******************************************************************************/
void InstanceTree::SetFilter(const std::set<std::string>& Types,
                             const std::string& NameFilter)
/******************************************************************************/
{
  types=Types;
  namefilter=NameFilter;
  gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(filtered));
}
/******************************************************************************/


/******************************************************************************/
std::string InstanceTree::GetChange(unsigned int Id)
/******************************************************************************/
{
  // Kopie mit kritischem Abschnitt
  lock->Lock();
  std::string ret=Id<=changes.size() ? changes[Id-1] : "";
  lock->Unlock();

  // return
  return ret;
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* InstanceTree::setup()
/******************************************************************************/
{
  // Datenmodell und Filter
  treestore=gtk_tree_store_new(5,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_POINTER,
                               G_TYPE_POINTER,G_TYPE_STRING);
  filtered=gtk_tree_model_filter_new(GTK_TREE_MODEL(treestore),NULL);
  gtk_tree_model_filter_set_visible_func(GTK_TREE_MODEL_FILTER(filtered),
                                         (GtkTreeModelFilterVisibleFunc)(filter),
                                         this,NULL);

  // Baum
  tree=gtk_tree_view_new();
  gtk_tree_view_set_model(GTK_TREE_VIEW(tree),GTK_TREE_MODEL(filtered));
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree),false);
  gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(tree),true);
 
  // Renderer und Spalte fuer Text (Namen, nicht editierbar)
  GtkCellRenderer* tr=gtk_cell_renderer_text_new();
  GtkTreeViewColumn* c1=
    gtk_tree_view_column_new_with_attributes("",tr,"text",0,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tree),c1);

  // Renderer und Spalte fuer Wert (editierbar)
  GtkCellRenderer* er=gtk_cell_renderer_text_new();
  g_object_set(er,"editable",TRUE,NULL);
  g_signal_connect(er,"edited",(GCallback)edited,this);
  GtkTreeViewColumn* c2=
    gtk_tree_view_column_new_with_attributes("",er,"text",1,NULL);
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
void InstanceTree::attribute_tree(GtkTreeIter r, Referenced* R,
                                  sarturis::ref<ConfigurationParent> c)
/******************************************************************************/
{
  // Attribute
  const attr_vec& a=c->GetAttributes();
  for (unsigned int i=0;i<a.size();++i)
  {
    if (a[i]->HasAccess())
    {
      GtkTreeIter n;
      gtk_tree_store_append(treestore,&n,&r);
      gtk_tree_store_set(treestore,&n,0,a[i]->GetName().c_str(),
                         1,a[i]->GetValue(R).c_str(),2,R,3,&(*(a[i])),-1);
    }
  }

  // Configurations
  const conf_vec& _c=c->GetConfigurations();
  for (unsigned int i=0;i<_c.size();++i)
  {
    if (_c[i]->HasAccess())
    {
      GtkTreeIter n;
      gtk_tree_store_append(treestore,&n,&r);
      gtk_tree_store_set(treestore,&n,0,_c[i]->GetName().c_str(),-1);

      attribute_tree(n,R,_c[i]);
    }
  }  
}
/******************************************************************************/


/******************************************************************************/
void InstanceTree::edited(GtkCellRendererText* cell, gchar* path_string,
                          gchar* new_text, InstanceTree* t)
/******************************************************************************/
{
  // Baumeintrag
  GtkTreeIter iter;
  if (gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(t->filtered),&iter,
                                          path_string)==false) return;

  // Im Baumeintrag selber setzen
  GtkTreeIter citer;
  gtk_tree_model_filter_convert_iter_to_child_iter(
    GTK_TREE_MODEL_FILTER(t->filtered),&citer,&iter);
  gtk_tree_store_set(t->treestore,&citer,1,new_text,-1);

  // Bestimme Attribute@Instance - String zum Setzen und Verteilen
  std::string key;
  GtkTreeIter rec=iter;
  GtkTreeIter par;
  while(1)
  {
    // Name des Baumeintrages
    gchar* name_str=0;
    gtk_tree_model_get(GTK_TREE_MODEL(t->filtered),&rec,0,&name_str,-1);

    // An key und dann name_str freigeben
    if (key.size()) key+="@";;
    key+=name_str;
    g_free(name_str);

    // Parent
    if (gtk_tree_model_iter_parent(GTK_TREE_MODEL(t->filtered),
                                   &par,&rec)==FALSE) break;
    rec=par;
  }

  // Selber setzen, bevor "=" und Wert angehangen werden
  Attribute::Set(key,new_text);

  // Mit "=" und Wert und dann merken
  key+="=";
  key+=new_text;
  t->lock->Lock();
  t->changes.push_back(key);
  t->lock->Unlock();
}
/******************************************************************************/


/******************************************************************************/
gboolean InstanceTree::filter(GtkTreeModel* model, GtkTreeIter* iter,
                              InstanceTree* t)
/******************************************************************************/
{
  // Name und Typ abfragen
  gchar* type_str=0;
  gchar* name_str=0;
  gtk_tree_model_get(model,iter,0,&name_str,4,&type_str,-1);
  if (!name_str) return TRUE;
  if (!type_str) return TRUE;

  // Sichtbarkeit
  gboolean visible=TRUE;
  if (t->types.find(type_str)==t->types.end()) visible=FALSE;
  if (!MATCH(t->namefilter.c_str(),name_str)) visible=FALSE;

  // Speicher freigeben und return
  g_free(type_str);  
  g_free(name_str);  
  return visible;
}
/******************************************************************************/
