/*
 * AndRestriction.cpp
 *
 *  Created on: Dec 6, 2009
 *      Author: alno
 */
#include "../../base/BaseInternal.h"

#include "AndRestriction.h"

namespace lspl { namespace patterns { namespace restrictions {

AndRestriction::AndRestriction() {
}

AndRestriction::~AndRestriction() {
}

bool AndRestriction::matches( const text::Transition * currentAnnotation, const matchers::Variable currentVar, const matchers::Context & ctx ) const {
	foreach( const Restriction & r, args )
		if ( !r.matches( currentAnnotation, currentVar, ctx ) )
			return false;

	return true;
}

void AndRestriction::dump( std::ostream & out, const std::string & tabs ) const {
	if ( args.size() <= 1 )
		throw std::logic_error( "Too less arguments" );

	args[0].dump( out );

	for ( uint i = 1; i < args.size(); ++i ) {
		out << " && ";
		args[i].dump( out );
	}
}

bool AndRestriction::equals( const Restriction & r ) const {
	if ( const AndRestriction * ar = dynamic_cast<const AndRestriction *>( &r ) ) {
		if ( ar->args.size() != args.size() ) return false;

		for ( uint i = 0, l = args.size(); i < l; ++ i )
			if ( !ar->args[i].equals( args[i] ) )
				return false;

		return true;
	} else {
		return false;
	}
}

bool AndRestriction::containsVariable( matchers::Variable var ) const {
	foreach( const Restriction & r, args )
		if ( r.containsVariable( var ) )
			return true;

	return false;
}

bool AndRestriction::containsVariables() const {
	foreach( const Restriction & r, args )
		if ( r.containsVariables() )
			return true;

	return false;
}

bool AndRestriction::containsCurrentAnnotation() const {
	foreach( const Restriction & r, args )
		if ( r.containsCurrentAnnotation() )
			return true;

	return false;
}

} } } // namespace lspl::patterns::matchers
