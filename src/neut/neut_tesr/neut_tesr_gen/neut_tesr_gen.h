/* This file is part of the Neper software package. */
/* Copyright (C) 2003-2019, Romain Quey. */
/* See the COPYING file in the top-level directory. */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef  NEUT_VOX_GEN_H
#define  NEUT_VOX_GEN_H

  extern void neut_tesr_cell (struct TESR Tesr, char **pcell);
  extern void neut_tesr_entity_qty (struct TESR Tesr, char *entity,
				    int *pqty);

  extern void neut_tesr_tesrqty (struct TESR Tesr, int *pqty);

  extern int neut_tesr_size (struct TESR Tesr, double *pvol);
  extern int neut_tesr_grid_volume (struct TESR Tesr, double *pvol);
  extern int neut_tesr_voxsize (struct TESR Tesr, double *psize);
  extern int neut_tesr_voxarea (struct TESR Tesr, double *parea);
  extern int neut_tesr_voxvolume (struct TESR Tesr, double *pvol);
  extern int neut_tesr_voxlengtheq (struct TESR Tesr, double *plengtheq);
  extern int neut_tesr_volume (struct TESR Tesr, double *pvol);
  extern int neut_tesr_grid_area (struct TESR Tesr, double *parea);
  extern int neut_tesr_area (struct TESR Tesr, double *parea);

  extern void neut_tesr_var_list (char *entity, char ***pvar, int *pvarqty);
  extern int neut_tesr_expr_val (struct TESR Tesr, char *entity,
				     int id, char *expr, double *val, int *pvalqty, char **ptype);
  extern int neut_tesr_expr_val_int (struct TESR Tesr, char *entity,
				     int id, char *expr, int *val, int *pvalqty, char **ptype);
  extern int neut_tesr_var_val (struct TESR Tesr,
				char *entity, int id, char *var, double *val, int* pvalqty,
				char **ptype);
  extern int neut_tesr_var_val_int (struct TESR Tesr,
				char *entity, int id, char *var, int *val,
				int *pvalqty, char **ptype);

  extern void neut_tesr_entity_expr_val (struct TESR Tesr, char *entity,
					 char *expr, double *val);

  extern void neut_tesr_var_dim (int dim, char *entity, char *var, int *pdim);

  extern int neut_tesr_var_val_all (struct TESR Tesr, char *entity,
				     char *var, double **val, int *valqty, char **ptype);
  extern int neut_tesr_expr_val_all (struct TESR Tesr, char *entity,
				     char *expr, double **val, int *valqty, char **ptype);

  extern int neut_tesr_pos_valid (struct TESR Tesr, int *pos);
  extern void neut_tesr_sizestring (struct TESR Tesr, char **psizestring);
#endif				/* NEUT_VOX_GEN_H */

#ifdef __cplusplus
}
#endif
