#include "catch.hpp"
#include "Time.h"

using namespace std;

TEST_CASE ("ms")
{
   SECTION("creation, int")
   {
      Time t0{0, 0, 0, 0};
      Time t1{12,30, 30, 500};
      Time t2{23,59,59, 666};

      CHECK_THROWS( Time{10,10,10, 12000} );
      CHECK_THROWS( Time{10,10,10, -23} );
      CHECK_THROWS( Time{5, 35, 35, 1000} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t0.get_ms()     == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t1.get_ms()     == 500 );

      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
      CHECK( t2.get_ms()     == 666 );

   }
   SECTION("Creation, with string")
   {
      Time t0{"00:00:00.000"};
      Time t1{"12:30:30.006"};
      Time t2{"23:59:59.700"};

      CHECK_THROWS( Time{"23:BB:59.007"} );
      CHECK_THROWS( Time{"10:10:00.-22"} );
      CHECK_THROWS( Time{"10:10:00.2348"} );
      CHECK_THROWS( Time{"10:10:00.-344444"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t0.get_ms()     == 0 );

      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t1.get_ms()     == 6 );

      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 ); 
      CHECK( t2.get_ms()     == 700  );
   }

   SECTION("- operator")
   {
      Time t0{"00:00:15.120"};
      Time t1{"00:00:20.100"};
      Time t2{"00:00:10.500"};
      CHECK( (t1 - t2) > 7.0 );
      CHECK( (t1 - t2) >8.0 );
      CHECK( (t1 - t2) < 123.0 );
      CHECK( (t1 - t2) == 9.6f );
      CHECK( (t0 - t2) < (t1 - t2) );

   }
      
      

}
