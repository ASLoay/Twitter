/*
*Local win32 Twitter tweetlistner.cpp
*Author: Loay ASHMAWY
*Company: Celad
*/
#include <dds/DCPS/Service_Participant.h>
#include <iostream>
#include "tweetDataReaderListnerImpl.h"
#include "TwitterTypeSupportImpl.h"
#include "TwitterTypeSupportC.h"
using namespace std;
tweetDataReaderListnerImpl::tweetDataReaderListnerImpl() {}

tweetDataReaderListnerImpl::~tweetDataReaderListnerImpl() {}

void tweetDataReaderListnerImpl::on_requested_deadline_missed(DDS::DataReader_ptr, const DDS::RequestedDeadlineMissedStatus &){}

void tweetDataReaderListnerImpl::on_requested_incompatible_qos(DDS::DataReader_ptr, const DDS::RequestedIncompatibleQosStatus &){}

void tweetDataReaderListnerImpl::on_liveliness_changed(DDS::DataReader_ptr, const DDS::LivelinessChangedStatus &){}

void tweetDataReaderListnerImpl::on_subscription_matched(DDS::DataReader_ptr, const DDS::SubscriptionMatchedStatus &){}

void tweetDataReaderListnerImpl::on_sample_rejected(DDS::DataReader_ptr, const DDS::SampleRejectedStatus&){}

void tweetDataReaderListnerImpl::on_sample_lost(DDS::DataReader_ptr, const DDS::SampleLostStatus&){}

void tweetDataReaderListnerImpl::on_data_available(DDS::DataReader_ptr reader) {

	Twitter::TweetDataReader_var tweet_dr = Twitter::TweetDataReader::_narrow(reader);
	if (!tweet_dr) {
		cerr << "ERROR: tweetDataReaderListnerImpl::on_data_available: _narrow failed." << endl;
		exit(1);
	}
	//reading tweet
	Twitter::Tweet tweet;
	DDS::SampleInfo si;
	DDS::ReturnCode_t status = tweet_dr->take_next_sample(tweet, si);

	if (status == DDS::RETCODE_OK && si.valid_data) {
		cout << "Tweet number " << tweet.count << " from @" << tweet.owner << " :" << endl
			<< "--" << tweet.text << endl;
	}
	else if (status == DDS::RETCODE_NO_DATA) {
		cerr << "INFO: No more tweets" << endl;
	}
}