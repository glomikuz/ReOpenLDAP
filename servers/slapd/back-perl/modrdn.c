/* $ReOpenLDAP$ */
/* Copyright (c) 2015,2016 Leonid Yuriev <leo@yuriev.ru>.
 * Copyright (c) 2015,2016 Peter-Service R&D LLC <http://billing.ru/>.
 *
 * This file is part of ReOpenLDAP.
 *
 * ReOpenLDAP is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * ReOpenLDAP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ---
 *
 * Copyright 1999-2014 The OpenLDAP Foundation.
 * Portions Copyright 1999 John C. Quillan.
 * Portions Copyright 2002 myinternet Limited.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.
 *
 * A copy of this license is available in file LICENSE in the
 * top-level directory of the distribution or, alternatively, at
 * <http://www.OpenLDAP.org/license.html>.
 */

#include "perl_back.h"

int
perl_back_modrdn(
	Operation	*op,
	SlapReply	*rs )
{
	PerlBackend *perl_back = (PerlBackend *) op->o_bd->be_private;
	int count;

	PERL_SET_CONTEXT( PERL_INTERPRETER );
	ldap_pvt_thread_mutex_lock( &perl_interpreter_mutex );

	{
		dSP; ENTER; SAVETMPS;

		PUSHMARK(sp) ;
		XPUSHs( perl_back->pb_obj_ref );
		XPUSHs(sv_2mortal(newSVpv( op->o_req_dn.bv_val , op->o_req_dn.bv_len )));
		XPUSHs(sv_2mortal(newSVpv( op->orr_newrdn.bv_val , op->orr_newrdn.bv_len )));
		XPUSHs(sv_2mortal(newSViv( op->orr_deleteoldrdn )));
		if ( op->orr_newSup != NULL ) {
			XPUSHs(sv_2mortal(newSVpv( op->orr_newSup->bv_val , op->orr_newSup->bv_len )));
		}
		PUTBACK ;

		count = call_method("modrdn", G_SCALAR);

		SPAGAIN ;

		if (count != 1) {
			croak("Big trouble in back_modrdn\n") ;
		}

		rs->sr_err = POPi;

		PUTBACK; FREETMPS; LEAVE ;
	}

	ldap_pvt_thread_mutex_unlock( &perl_interpreter_mutex );

	send_ldap_result( op, rs );

	Debug( LDAP_DEBUG_ANY, "Perl MODRDN\n" );
	return( 0 );
}
