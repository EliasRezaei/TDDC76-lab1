#include "catch.hpp"
#include "Time.h"

using namespace std;

TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }

   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS( Time{"13:35:60"} );
      CHECK_THROWS( Time{"13:60:35"} );
      CHECK_THROWS( Time{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }
}
TEST_CASE ("is_am") 
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   CHECK       ( t0.is_am() );
   CHECK_FALSE ( t1.is_am() );
   // Fill with extra corner cases!
}


TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   SECTION("24 hour format no argument")
   {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "11:59:59" );
      CHECK( t2.to_string() == "12:00:00" );
      CHECK( t3.to_string() == "13:00:00" );
      CHECK( t4.to_string() == "23:59:59" );
   }
   
   SECTION("24 hour format with argument")
   {
      CHECK( t0.to_string(TimeFormat::Format24h) == "00:00:00" );
      CHECK( t1.to_string(TimeFormat::Format24h) == "11:59:59" );
      CHECK( t2.to_string(TimeFormat::Format24h) == "12:00:00" );
      CHECK( t3.to_string(TimeFormat::Format24h) == "13:00:00" );
      CHECK( t4.to_string(TimeFormat::Format24h) == "23:59:59" );
   } 

   SECTION("12 hour format")
   {
      CHECK( t0.to_string(TimeFormat::Format12h) == "00:00:00am" );
      CHECK( t1.to_string(TimeFormat::Format12h) == "11:59:59am" );
      CHECK( t2.to_string(TimeFormat::Format12h) == "00:00:00pm" );
      CHECK( t3.to_string(TimeFormat::Format12h) == "01:00:00pm" );
      CHECK( t4.to_string(TimeFormat::Format12h) == "11:59:59pm" );
   }
}

// Fill with more tests of other functions and operators!

TEST_CASE ("operators")
{
   Time t0{};
   Time t00{};
   Time t01{0, 0, 1};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   Time t5{23, 59, 59};

   Time t6{10, 59, 59};
   Time t7{11, 0, 0};

   Time t9{0, 0, 59};
   Time t10{0, 1, 0};



   SECTION("==")
   {
      CHECK( t4 == t5);
   }
   SECTION("<")
   {
      CHECK( t0 < t2);
   }
   SECTION("<=")
   {
      CHECK( t0 <= t2);
      CHECK( t4 <= t5);
   }
   SECTION(">")
   {
      CHECK(t4>t3);
      CHECK(t4>t1);
   }
   
   SECTION("t++")
   {
      //auto t22 = t0++;
      CHECK(++t4 == t0); // day rollover
      CHECK(++t6 == t7); // hour rollover
      CHECK(++t9 == t10); // hour rollover
      CHECK(t0++ == t00);
   }

   SECTION("++t")
   {
      CHECK(++t0 > t00);
      CHECK(++t1==t2);
   }



}





TEST_CASE ("ms")
{
   SECTION("creation, int")
   {
      Time t0{0, 0, 0, 0};
      Time t1{12,30,30, 500};
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
