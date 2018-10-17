//
//  ncbi-jwt-ut.cpp
//  ncbi-oauth-test
//
//  Created by User on 7/30/18.
//  Copyright © 2018 NCBI. All rights reserved.
//

#include "gtest/gtest.h"
#include <ncbi/jws.hpp>
#include <ncbi/jwt.hpp>

#include <iostream>

namespace ncbi
{
    /* JWT
     *
     **********************************************************************************/
    class JWTFixture_BasicConstruction : public :: testing :: Test
    {
    public:
        void SetUp ()
        {
            jws_fact = new JWSFactory ( "HS256", "ncbi", "blarky2", "blarky2" );
            jwt_fact = new JWTFactory ( * jws_fact );
            jwt_fact -> setIssuer ( "ncbi" );
            jwt_fact -> setDuration ( 15 );
        }
        
        void TearDown ()
        {
            delete jwt_fact;
            delete jws_fact;
        }
        
    protected:

        JWSFactory * jws_fact;
        JWTFactory * jwt_fact;
    };
   
    TEST_F ( JWTFixture_BasicConstruction, JWT_Hello )
    {
        JWTClaims claims = jwt_fact -> make ();
        claims . addClaimOrDeleteValue ( "hello", JSONValue :: makeString ( "there" ) );
        std :: cout
            << "hello test:\n"
            << "  JSON:\n"
            << "    "
            << claims . toJSON ()
            << '\n'
            ;
        JWT jwt = jwt_fact -> sign ( claims );
        std :: cout
            << "  JWT:\n"
            << "    "
            << jwt
            << std :: endl
            ;
    }

} // namespace
