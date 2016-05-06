/*
Milu v3.0 - A Higher Order Mutation Testing Tool

Copyright (c) 2011, Yue Jia
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the University College London nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Mutator.h"
#include "ASTNodeUtil.h"

static gboolean mutator_milu_integer_constant_replacement_node_checking(ASTNode *);
static gboolean mutator_milu_integer_constant_replacement_clean(ASTNode * node, gint type);
static gboolean mutator_milu_integer_constant_replacement_mutate(ASTNode * node, gint type);


Mutator * mutator_milu_integer_constant_replacement()
{
	Mutator * mut = mutator_new("Integer constant replace operator", "");
	mut->node_checking = & mutator_milu_integer_constant_replacement_node_checking;
	mut->mutate = & mutator_milu_integer_constant_replacement_mutate;
	mut->clean = & mutator_milu_integer_constant_replacement_clean;
	mut->size = 9;
	return mut;
}

static gboolean mutator_milu_integer_constant_replacement_node_checking(ASTNode * node)
{
	if(is_ASTNode_kind_integer_literal(node))
		    return TRUE;
	return FALSE;
}

static gboolean mutator_milu_integer_constant_replacement_mutate(ASTNode * node, gint type)
{
	ASTNodeType_save_original_text(node);
	switch(type)
	{
		case 1:
                        if(atoi(node->text) != -1)
			    set_ASTNode_text (node, "-1");
                        else
			    set_ASTNode_text (node, "-819");
			return TRUE;

		case 2:
                        if(atoi(node->text) != 0)
			    set_ASTNode_text (node, "0");
                        else
			    set_ASTNode_text (node, "607");
			return TRUE;

		case 3:
                        if(atoi(node->text) != 1)
			    set_ASTNode_text (node, "1");
                        else
			    set_ASTNode_text (node, "302");
			return TRUE;
		case 4:
			set_ASTNode_text (node, g_strdup_printf("%d", atoi(node->text) + 1));
			return TRUE;
		case 5:
			set_ASTNode_text (node, g_strdup_printf("%d", atoi(node->text) - 1));
			return TRUE;
//		case 6:
//			set_ASTNode_text (node, g_strdup_printf("%d", atoi(node->text) * -1));
//			return TRUE;
		case 6:
                        if(atoi(node->text) != 1023)
			    set_ASTNode_text (node, "1023");
                        else
			    set_ASTNode_text (node, "511");
			return TRUE;
		case 7:
                        if(atoi(node->text) != 32767)
			    set_ASTNode_text (node, "32767");
                        else
			    set_ASTNode_text (node, "16383");
			return TRUE;
		case 8:
                        set_ASTNode_text (node, g_strdup_printf("%d", atoi(node->text) * 2));
			return TRUE;
		case 9:
                        if(atoi(node->text) >= 4 || atoi(node->text) <= -4)
			    set_ASTNode_text (node, g_strdup_printf("%d", atoi(node->text) / 2));
                        else
			    set_ASTNode_text (node, g_strdup_printf("%d", atoi(node->text) * 3));
			return TRUE;
		default:
			break;
	}

	return FALSE;
}

static gboolean mutator_milu_integer_constant_replacement_clean(ASTNode * node, gint type)
{
	ASTNodeType_restore_original_text(node);
	return TRUE;
}

