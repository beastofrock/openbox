/* -*- indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

   obt/xml.h for the Openbox window manager
   Copyright (c) 2003-2007   Dana Jansens

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the COPYING file for a copy of the GNU General Public License.
*/

#ifndef __obt_xml_h
#define __obt_xml_h

#include <libxml/parser.h>
#include <glib.h>

G_BEGIN_DECLS

typedef struct _ObtXmlInst ObtXmlInst;

typedef void (*ObtXmlCallback)(xmlNodePtr node, gpointer data);

ObtXmlInst* obt_xml_instance_new(void);
void obt_xml_instance_ref(ObtXmlInst *inst);
void obt_xml_instance_unref(ObtXmlInst *inst);

void obt_xml_new_file(ObtXmlInst *inst,
                      const gchar *root_node);

gboolean obt_xml_load_file(ObtXmlInst *inst,
                           const gchar *path,
                           const gchar *root_node);
gboolean obt_xml_load_cache_file(ObtXmlInst *inst,
                                 const gchar *domain,
                                 const gchar *filename,
                                 const gchar *root_node);
gboolean obt_xml_load_config_file(ObtXmlInst *inst,
                                  const gchar *domain,
                                  const gchar *filename,
                                  const gchar *root_node);
gboolean obt_xml_load_data_file(ObtXmlInst *inst,
                                const gchar *domain,
                                const gchar *filename,
                                const gchar *root_node);
gboolean obt_xml_load_theme_file(ObtXmlInst *inst,
                                 const gchar *theme,
                                 const gchar *domain,
                                 const gchar *filename,
                                 const gchar *root_node);
gboolean obt_xml_load_mem(ObtXmlInst *inst,
                          gpointer data, guint len, const gchar *root_node);

gboolean obt_xml_save_file(ObtXmlInst *inst,
                           const gchar *path,
                           gboolean pretty);
gboolean obt_xml_save_cache_file(ObtXmlInst *inst,
                                 const gchar *domain,
                                 const gchar *filename,
                                 gboolean pretty);

xmlDocPtr obt_xml_doc(ObtXmlInst *inst);
xmlNodePtr obt_xml_root(ObtXmlInst *inst);

/*! Returns the path to the file loaded by @inst, if one exists, or NULL.
  The returned string is owned by @inst and will be freed along with it.
 */
const gchar* obt_xml_file_path(ObtXmlInst *inst);

void obt_xml_close(ObtXmlInst *inst);

void obt_xml_register(ObtXmlInst *inst, const gchar *tag,
                      ObtXmlCallback func, gpointer data);
void obt_xml_unregister(ObtXmlInst *inst, const gchar *tag);
void obt_xml_tree(ObtXmlInst *i, xmlNodePtr node);
void obt_xml_tree_from_root(ObtXmlInst *i);


/* helpers */

xmlNodePtr obt_xml_find_sibling(xmlNodePtr node, const gchar *name);

guint    obt_xml_node_line     (xmlNodePtr node);
gboolean obt_xml_node_contains (xmlNodePtr node, const gchar *val);
gchar   *obt_xml_node_string   (xmlNodePtr node);  /* strips whitespace */
gchar   *obt_xml_node_string_raw(xmlNodePtr node); /* unstripped version */
gint     obt_xml_node_int      (xmlNodePtr node);
gboolean obt_xml_node_bool     (xmlNodePtr node);

void obt_xml_node_set_string(xmlNodePtr node, const gchar *s);
void obt_xml_node_set_int(xmlNodePtr node, gint i);
void obt_xml_node_set_bool(xmlNodePtr node, gboolean b);

gboolean obt_xml_attr_contains (xmlNodePtr node, const gchar *name,
                                const gchar *val);
gboolean obt_xml_attr_string   (xmlNodePtr node, const gchar *name,
                                gchar **value);
gboolean obt_xml_attr_int      (xmlNodePtr node, const gchar *name,
                                gint *value);
gboolean obt_xml_attr_bool     (xmlNodePtr node, const gchar *name,
                                gboolean *value);

/* path based operations */

/*! Returns the node in the given @subtree, at the given @path.  If the node is
  not found, it is created, along with any parents.

  The path has a structure follows.
  - <name> - specifies a child of the current position in the subtree
  - :foo=bar - specifies an attribute and its value.  this can be appended to
    a <name> or to another attribute
  - / - specifies to move one level deeper in the tree

  An example:
  - theme/font:place=ActiveWindow/size refers to the size node at this
    position:
    - <theme><font place="ActiveWindow"><size /></font></theme>

  @subtree The root of the search.
  @path A string specifying the search path.
  @default_value If the node is not found, it is created with this value
    contained within.
*/
xmlNodePtr obt_xml_path_get_node(xmlNodePtr subtree, const gchar *path,
                                 const gchar *default_value);
/*! Similar to obt_xml_path_get_node(), but returns a list of nodes that
  match the given path.
  Given xml as <a><b>1</b><b>2</b><b>3</b></a>, the path "a/b" would return
  the list of all nodes named b.
*/
GList* obt_xml_path_get_list(xmlNodePtr subtree, const gchar *path);
/*! Removes a specified node from the tree. */
void obt_xml_path_delete_node(xmlNodePtr subtree, const gchar *path);

gchar* obt_xml_path_string(xmlNodePtr subtree, const gchar *path,
                          const gchar *default_value);
int obt_xml_path_int(xmlNodePtr subtree, const gchar *path,
                     const gchar *default_value);
gboolean obt_xml_path_bool(xmlNodePtr subtree, const gchar *path,
                           const gchar *default_value);

void obt_xml_path_set_string(xmlNodePtr subtree, const gchar *path,
                             const gchar *value);
void obt_xml_path_set_int(xmlNodePtr subtree, const gchar *path,
                          gint value);
void obt_xml_path_set_bool(xmlNodePtr subtree, const gchar *path,
                           gboolean value);

G_END_DECLS

#endif
