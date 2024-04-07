//
// Created by Daniel St. John on 12/15/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "catch.hpp"
#include "BigInteger.h"
#include "time_metrics.h"

using namespace dsj;
using namespace dsj::utils;

#include <string>

using namespace std;

TEST_CASE("6133", "[isPrime true]") {

    BigInteger candidate("6133");
    TimeMetrics::Start("01");
    bool isPrime = candidate.IsPrime();
    cout << candidate << " : is prime " << isPrime << endl;
    TimeMetrics::Stop("01");
    cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average("01") << endl;
    REQUIRE(isPrime == true);
}

TEST_CASE("6134", "[isPrime false]") {

    BigInteger candidate("6134");
    TimeMetrics::Start("01");
    bool isPrime = candidate.IsPrime();
    TimeMetrics::Stop("01");
    cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average("01") << endl;
    REQUIRE(isPrime == false);
}

TEST_CASE("6134123217", "[isPrime false]") {

    BigInteger candidate("6134123217");
    TimeMetrics::Start("01");
    bool isPrime = candidate.IsPrime();
    TimeMetrics::Stop("01");
    cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average("01") << endl;
    REQUIRE(isPrime == false);
}

TEST_CASE("1732642631", "[prime true]") {

    BigInteger candidate("1732642631");
    TimeMetrics::Start("01");
    bool isPrime = candidate.IsPrime();
    TimeMetrics::Stop("01");
    cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average("01") << endl;
    REQUIRE(isPrime == false);
}


TEST_CASE("123217", "[isPrime true]") {

    BigInteger candidate("123217");
    TimeMetrics::Start("01");
    bool isPrime = candidate.IsPrime();
    TimeMetrics::Stop("01");
    cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average("01") << endl;
    REQUIRE(isPrime == true);

}

TEST_CASE("100,000,045,007", "[candidate]") {

    BigInteger candidate("100,000,045,007");
    TimeMetrics::Start("01");
    bool isPrime = candidate.IsPrime();
    TimeMetrics::Stop("01");
    cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average("01") << endl;
    //REQUIRE(isPrime == true);
}

TEST_CASE("isPrime", "[3-1000]") {

    for (unsigned long i = 2; i < 1000; i++) {
        BigInteger candidate(i);
        TimeMetrics::Start(to_string(i));
        bool isPrime = candidate.IsPrime();
        TimeMetrics::Stop(to_string(i));
        if ( isPrime){
            cout << candidate << " time : " << TimeMetrics::Average(to_string(i)) << endl;
        }
        //cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average(to_string(i)) << endl;
    }
}

TEST_CASE("isPrime 10,000", "[10,000-11,000]") {

    for (unsigned long i = 10000; i < 11000; i++) {
        BigInteger candidate(i);
        TimeMetrics::Start(to_string(i));
        bool isPrime = candidate.IsPrime();
        TimeMetrics::Stop(to_string(i));
        if ( isPrime){
            cout << candidate << " time : " << TimeMetrics::Average(to_string(i)) << endl;
        }
        //cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average(to_string(i)) << endl;
    }
}

TEST_CASE("isPrime 100,000,000", "[10,000-11,000]") {

    for (unsigned long i = 100000000; i < 1000000100; i++) {
        BigInteger candidate(i);
        TimeMetrics::Start(to_string(i));
        bool isPrime = candidate.IsPrime();
        TimeMetrics::Stop(to_string(i));
        if ( isPrime){
            cout << candidate << " time : " << TimeMetrics::Average(to_string(i)) << endl;
        }
        //cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average(to_string(i)) << endl;
    }
}


TEST_CASE("M123", "[try]") {

    auto M4423 = "2855425422282796139015635661021640083261642386447028891992474566022844003906006538759545715055398432397545139158961502978783993770560714351697472211079887911982009884775313392142827720160590099045866862549890848157354224804090223442975883525260043838906326161240763173874168811485924861883618739041757831456960169195743907655982801885990355784485910776836771755204340742877265780062667596159707595213278285556627816783856915818444364448125115624281367424904593632128101802760960881114010033775703635457251209240736469215767971461993876199656030268026179011813292501232304644443862230887792460937377301248168167242449367447448853777015578300688085264816151306714481479028836666406225727466527578712737464923109637500117090189078626332461957879573142569380507305611967758033808433338198750090296883193591309526982131114132239335649017848872898228815628260081383129614366384594543114404375382154287127774560644785856415921332844358020642271469491309176271644704168967807009677359042980890961675045292725800084350034483162829708990272864998199438764723457427626372969484830475091717418618113068851879274862261229334136892805663438446664632657247616727560839105650528975713899320211121495795311427946254553305387067821067601768750977866100460014602138408448021225053689054793742003095722096732954750721718115531871310231057902608580607";

    BigInteger m4423(M4423);

    BigInteger candidate("100,000,045,007");
    TimeMetrics::Start("01");
    bool isPrime = candidate.IsPrime();
    TimeMetrics::Stop("01");
    cout << candidate << " : is prime " << isPrime << " time " << TimeMetrics::Average("01") << endl;

}