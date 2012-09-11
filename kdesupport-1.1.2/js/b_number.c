/*
 * The builtin Number object.
 * Copyright (c) 1998 New Generation Software (NGS) Oy
 *
 * Author: Markku Rossi <mtr@ngs.fi>
 */

/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA
 */

/*
 * $Source: /home/kde/kdesupport/js/b_number.c,v $
 * $Id: b_number.c,v 1.1.1.1 1998/08/09 21:05:34 kulow Exp $
 */

/* TODO: global method: Number (obj) => number */

#include "jsint.h"

/*
 * Types and definitions.
 */

/* Class context. */
struct number_ctx_st
{
  JSSymbol s_MAX_VALUE;
  JSSymbol s_MIN_VALUE;
  JSSymbol s_NaN;
  JSSymbol s_NEGATIVE_INFINITY;
  JSSymbol s_POSITIVE_INFINITY;
};

typedef struct number_ctx_st NumberCtx;


/*
 * Static functions.
 */

/* Method proc. */
static int
method (JSVirtualMachine *vm, JSBuiltinInfo *builtin_info,
	void *instance_context, JSSymbol method, JSNode *result_return,
	JSNode *args)
{
  JSNode *n = instance_context;
  char buf[256];

  if (method == vm->syms.s_toString)
    {
      if (n)
	{
	  int radix = 10;

	  if (args->u.vinteger == 0)
	    ;
	  else if (args->u.vinteger == 1)
	    {
	      if (args[1].type != JS_INTEGER)
		goto argument_type_error;

	      radix = args[1].u.vinteger;
	    }
	  else
	    goto argument_error;

	  if (n->type == JS_INTEGER)
	    {
	      switch (radix)
		{
		case 8:
		  sprintf (buf, "%o", (unsigned int) n->u.vinteger);
		  break;

		case 10:
		  sprintf (buf, "%ld", n->u.vinteger);
		  break;

		case 16:
		  sprintf (buf, "%lx", (unsigned long) n->u.vinteger);
		  break;

		default:
		  sprintf (vm->error, "Number.%s(): illegal radix %d",
			   js_vm_symname (vm, method), radix);
		  break;
		}
	    }
	  else if (n->type == JS_FLOAT)
	    sprintf (buf, "%g", n->u.vfloat);
	  else
	    sprintf (buf, "NaN");

	  js_vm_make_string (vm, result_return, buf, strlen (buf));
	}
      else
	{
	  if (args->u.vinteger != 0)
	    goto argument_error;
	  js_vm_make_static_string (vm, result_return, "Number", 6);
	}
    }
  /* ********************************************************************** */
  else
    return JS_PROPERTY_UNKNOWN;

  return JS_PROPERTY_FOUND;


  /*
   * Error handling.
   */

 argument_error:
  sprintf (vm->error, "Number.%s(): illegal amount of arguments",
	   js_vm_symname (vm, method));
  js_vm_error (vm);

 argument_type_error:
  sprintf (vm->error, "Number.%s(): illegal argument",
	   js_vm_symname (vm, method));
  js_vm_error (vm);

  /* NOTREACHED */
  return 0;
}

/* Property proc. */
static int
property (JSVirtualMachine *vm, JSBuiltinInfo *builtin_info,
	  void *instance_context, JSSymbol property, int set, JSNode *node)
{
  NumberCtx *ctx = builtin_info->obj_context;

  /* The default result type. */
  node->type = JS_FLOAT;

  if (property == ctx->s_MAX_VALUE)
    {
      if (set)
	goto immutable;

      node->u.vfloat = DBL_MAX;
    }
  else if (property == ctx->s_MIN_VALUE)
    {
      if (set)
	goto immutable;

      node->u.vfloat = DBL_MIN;
    }
  else if (property == ctx->s_NaN)
    {
      if (set)
	goto immutable;

      node->type = JS_NAN;
    }
  else if (property == ctx->s_NEGATIVE_INFINITY)
    {
      if (set)
	goto immutable;

      node->u.vfloat = -HUGE_VAL;
    }
  else if (property == ctx->s_POSITIVE_INFINITY)
    {
      if (set)
	goto immutable;

      node->u.vfloat = HUGE_VAL;
    }
  else
    {
      if (!set)
	node->type = JS_UNDEFINED;

      return JS_PROPERTY_UNKNOWN;
    }

  return JS_PROPERTY_FOUND;


  /*
   * Error handling.
   */

 immutable:
  sprintf (vm->error, "Number.%s: immutable property",
	   js_vm_symname (vm, property));
  js_vm_error (vm);

  /* NOTREACHED */
  return 0;
}


/*
 * Global functions.
 */

void
js_builtin_Number (JSVirtualMachine *vm)
{
  NumberCtx *ctx;
  JSNode *n;
  JSBuiltinInfo *info;

  ctx = js_calloc (vm, 1, sizeof (*ctx));

  ctx->s_MAX_VALUE		= js_vm_intern (vm, "MAX_VALUE");
  ctx->s_MIN_VALUE		= js_vm_intern (vm, "MIN_VALUE");
  ctx->s_NaN			= js_vm_intern (vm, "NaN");
  ctx->s_NEGATIVE_INFINITY	= js_vm_intern (vm, "NEGATIVE_INFINITY");
  ctx->s_POSITIVE_INFINITY	= js_vm_intern (vm, "POSITIVE_INFINITY");

  info = js_vm_builtin_info_create (vm);
  vm->prim[JS_INTEGER]	= info;
  vm->prim[JS_FLOAT]	= info;
  vm->prim[JS_NAN]	= info;

  info->method_proc 		= method;
  info->property_proc		= property;
  info->obj_context		= ctx;
  info->obj_context_delete	= js_free;

  /* Define it. */
  n = &vm->globals[js_vm_intern (vm, "Number")];
  js_vm_builtin_create (vm, n, info, NULL);
}
