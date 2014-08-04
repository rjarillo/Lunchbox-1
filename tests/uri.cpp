
/* Copyright (c) 2013-2014, ahmet.bilgili@epfl.ch
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <test.h>
#include <lunchbox/uri.h>

int main( int, char ** )
{
    try
    {
        const std::string uriStr =
            "http://bob@www.example.com:8080/path/?key=value,foo=bar#fragment";
        const lunchbox::URI uri( uriStr );

        TESTINFO( uri.getScheme() == "http", uri.getScheme() );
        TESTINFO( uri.getHost() == "www.example.com", uri.getHost( ));
        TESTINFO( uri.getUserinfo() == "bob", uri.getUserinfo( ));
        TESTINFO( uri.getPort() == 8080, uri.getPort( ));
        TESTINFO( uri.getPath() == "/path/", uri.getPath( ));
        TESTINFO( uri.getQuery() == "key=value,foo=bar", uri.getQuery( ));
        TESTINFO( uri.getFragment() == "fragment", uri.getFragment( ));

        TEST( uri.findQuery( "key" ) != uri.queryEnd( ));
        TEST( uri.findQuery( "foo" ) != uri.queryEnd( ));
        TEST( uri.findQuery( "bar" ) == uri.queryEnd( ));
        TESTINFO( uri.findQuery( "key" )->second == "value",
                  uri.findQuery( "key" )->second );
        TESTINFO( uri.findQuery( "foo" )->second == "bar",
                  uri.findQuery( "foo" )->second );

        std::stringstream sstr;
        sstr << uri;
        TESTINFO( sstr.str() == uriStr, sstr.str() << " " <<  uriStr );
    }
    catch( std::exception& exception )
    {
        LBERROR << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        const std::string uriStr = "Helloworld";
        lunchbox::URI uri( uriStr );
    }
    catch( std::exception& exception )
    {
        return EXIT_SUCCESS;
    }

    TESTINFO( false, "Did not get exception on malformed URI" );
    return EXIT_FAILURE;
}
