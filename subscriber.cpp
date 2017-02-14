/*
*Local win32 Twitter Subscriber
*Author: Loay ASHMAWY
*Company: Celad
*/
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/SubscriberImpl.h>
#include <dds/DCPS/BuiltInTopicUtils.h>
#include <iostream>
#include "tweetDataReaderListnerImpl.h"
#include "TwitterTypeSupportImpl.h"

const char* TYPE_NAME = "tweet";
DDS::DomainId_t TWITTER_DOMAIN_ID = 1500;