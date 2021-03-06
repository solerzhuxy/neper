/* This file is part of the Neper software package. */
/* Copyright (C) 2003-2019, Romain Quey. */
/* See the COPYING file in the top-level directory. */

#include "net_stat_.h"

void
net_stat_tess (FILE * file, char *entity, char *format, struct TESS Tess)
{
  int qty;
  int i, j, status, invalqty;
  double val;
  char **invar = NULL, *valstring = NULL, *type = NULL;
  double **data = NULL;
  char **datatype = NULL;

  neut_tess_entity_qty (Tess, entity, &qty);

  ut_string_separate (format, NEUT_SEP_NODEP, &invar, &invalqty);

  data = ut_alloc_2d (invalqty, qty + 1);
  datatype = ut_alloc_1d_pchar (invalqty);

  for (j = 0; j < invalqty; j++)
    if (!strstr (invar[j], "list"))
    {
      status = neut_tess_var_val_all (Tess, NULL, NULL, NULL,
				      entity, invar[j], data[j],
				      &(datatype[j]));
      if (status != 0)
	ut_print_message (2, 0, "Expression `%s' could not be processed.\n",
			  invar[j]);
    }

  for (i = 1; i <= qty; i++)
    for (j = 0; j < invalqty; j++)
    {
      val = 0;
      if (!strstr (invar[j], "list"))
      {
	val = data[j][i];
	ut_string_string (datatype[j], &type);
	status = 0;
      }
      else
	status =
	  neut_tess_var_val_string (Tess, entity, i, invar[j], &valstring,
				    &type);

      if (status == 0)
      {
	if (!strcmp (type, "%d"))
	  fprintf (file, "%d", ut_num_d2ri (val));
	else if (!strcmp (type, "%f"))
	  fprintf (file, "%.12f", val);
	else if (!strcmp (type, "%s"))
	  fprintf (file, "%s", valstring);
	else
	  ut_error_reportbug ();
      }
      else
	ut_print_message (2, 0, "Expression `%s' could not be processed.\n",
			  invar[j]);

      fprintf (file, (j < invalqty - 1) ? " " : "\n");
    }

  ut_free_2d_char (invar, invalqty);
  ut_free_1d_char (type);
  ut_free_1d_char (valstring);
  ut_free_2d (data, invalqty);
  ut_free_2d_char (datatype, invalqty);

  return;
}

void
net_stat_point (FILE * file, char *format, struct POINT Point,
		struct TESS Tess)
{
  int i, j, status, invalqty, var_qty;
  double val;
  char **invar = NULL, *type = NULL, **vars = NULL;
  struct NODES Nodes;
  struct MESH Mesh;

  neut_nodes_set_zero (&Nodes);
  neut_mesh_set_zero (&Mesh);

  ut_string_separate (format, NEUT_SEP_NODEP, &invar, &invalqty);

  neut_point_var_list (&vars, &var_qty);

  for (i = 1; i <= Point.PointQty; i++)
    for (j = 0; j < invalqty; j++)
    {
      status =
	neut_point_var_val (Point, i, Tess, Nodes, Mesh, invar[j], &val,
			    &type);

      if (status == 0)
      {
	if (!strcmp (type, "%d"))
	  fprintf (file, "%d", ut_num_d2ri (val));
	else if (!strcmp (type, "%f"))
	  fprintf (file, "%.12f", val);
	else
	  ut_error_reportbug ();
      }
      else
	ut_print_message (2, 0, "Expression `%s' could not be processed.\n",
			  invar[j]);

      fprintf (file, (j < invalqty - 1) ? " " : "\n");
    }

  ut_free_2d_char (invar, invalqty);
  ut_free_2d_char (vars, var_qty);
  ut_free_1d_char (type);

  neut_nodes_free (&Nodes);
  neut_mesh_free (&Mesh);

  return;
}

void
net_stat_tesr (FILE * file, char *entity, char *format, struct TESR *pTesr)
{
  int i, j, qty, status, invalqty, valqty;
  double val[10];
  char **invar = NULL, *type = NULL;
  double **data = NULL;
  int *dataqty = NULL;
  char **datatype = NULL;
  double *coo = ut_alloc_1d (3);

  neut_tesr_entity_qty (*pTesr, entity, &qty);

  ut_string_separate (format, NEUT_SEP_NODEP, &invar, &invalqty);

  if (!strcmp (entity, "cell"))
  {
    if ((strstr (format, "x") || strstr (format, "y") || strstr (format, "z")) && !(*pTesr).CellCoo)
      neut_tesr_init_cellcoo (pTesr);
    if (strstr (format, "vol") && !(*pTesr).CellVol)
      neut_tesr_init_cellvol (pTesr);
    if (strstr (format, "convexity") && !(*pTesr).CellConvexity)
      neut_tesr_init_cellconvexity (pTesr);
  }

  data = ut_alloc_2d (invalqty, qty + 1);
  dataqty = ut_alloc_1d_int (invalqty);
  datatype = ut_alloc_1d_pchar (invalqty);

  for (i = 1; i <= qty; i++)
    for (j = 0; j < invalqty; j++)
    {
      status = neut_tesr_expr_val (*pTesr, entity, i, invar[j], val, &valqty, &type);
      if (status != 0)
	ut_error_expression (invar[j]);

      ut_array_1d_fprintf_nonl (file, val, valqty, !strcmp (type, "%f") ? "%.12f" : type);
      fprintf (file, (j < invalqty - 1) ? " " : "\n");
    }

  ut_free_2d_char (invar, invalqty);
  ut_free_1d_char (type);
  ut_free_2d (data, invalqty);
  ut_free_1d_int (dataqty);
  ut_free_2d_char (datatype, invalqty);
  ut_free_1d (coo);

  return;
}
