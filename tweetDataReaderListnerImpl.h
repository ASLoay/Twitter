/*
*Local win32 Twitter tweetlistner.h
*Author: Loay ASHMAWY
*Company: Celad
*/

#ifndef TWEET_DATA_READER_LISTENER_IMPL
#define TWEET_DATA_READER_LISTENER_IMPL
#include <dds/DdsDcpsSubscriptionC.h>
#include <dds/DCPS/LocalObject.h>


class tweetDataReaderListnerImpl :public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
{
public:
	tweetDataReaderListnerImpl();

	virtual ~tweetDataReaderListnerImpl(void);

	virtual void on_requested_deadline_missed(DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus & status);

	virtual void on_requested_incompatible_qos(DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus & status);

	virtual void on_liveliness_changed(DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus & status);

	virtual void on_subscription_matched(DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus & status);

	virtual void on_sample_rejected(DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status);

	virtual void on_data_available(DDS::DataReader_ptr reader);

	virtual void on_sample_lost(DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status);

};
#endif // !TWEET_DATA_READER_LISTENER_IMPL

