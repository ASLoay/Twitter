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
#include <list>
#include "tweetDataReaderListnerImpl.h"
#include "dds/DCPS/StaticIncludes.h"
#include "TwitterTypeSupportImpl.h"

const char* TYPE_NAME = "tweet";
DDS::DomainId_t TWITTER_DOMAIN_ID = 1500;
using namespace std;

int main(int argc, char *argv[]) {
	string user;
	list<string> userList;
	list<string>::iterator i;

	try {
		cout << "Initializing Twitter for the subscriber..." << endl;
		// Initialize DomainParticipantFactory
		DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);

		// Create DomainParticipant
		DDS::DomainParticipant_var participant = dpf->create_participant(TWITTER_DOMAIN_ID, PARTICIPANT_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);

		if (!participant) {
			cerr << "ERROR: Subscriber::main(): failed to create participant" << endl;
			return -1;
		}

		// Register TypeSupport (Twitter::Tweet)
		Twitter::TweetTypeSupport_var ts = new Twitter::TweetTypeSupportImpl;
		if (ts->register_type(participant, TYPE_NAME) != DDS::RETCODE_OK) {
			cerr << "ERROR: Subscriber::main(): failed to register_type" << TYPE_NAME << endl;
			return -1;
		}

		//Create subscriber
		DDS::Subscriber_var subscriber = participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		if (!subscriber) {
			cerr << "ERROR: Subscriber::main(): failed to create subscriber" << endl;
			return -1;
		}
		cout << "********************************************************" << endl;
		cout << "*               Begin subscribing!                     *" << endl;
		cout << "********************************************************" << endl;
		//ask for the subscriptions
		while (true) {
			cout << "Enter publisher's username. To exit press \"X\": ";
			getline(cin, user);
			if (user == "X") {
				break;
			}
			userList.push_back(user);
		}
		for (i = userList.begin(); i != userList.end(); ++i) {

			//Create topics associated to the userList
			DDS::Topic_var topic = participant->create_topic((*i).c_str(), TYPE_NAME, TOPIC_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
			if (!topic) {
				cerr << "ERROR: Subscriber::main(): failed to create topic" << endl;
				return -1;
			}

			//Create Listeners
			tweetDataReaderListnerImpl* listner = new tweetDataReaderListnerImpl();
			if (CORBA::is_nil(listner)) {
				cerr << "ERROR: Subscriber::main(): listener is nil." << endl;
				return -1;
			}
			//Create Readers
			DDS::DataReader_var reader = subscriber->create_datareader(topic,DATAREADER_QOS_DEFAULT, listner,OpenDDS::DCPS::DEFAULT_STATUS_MASK);
			if (!reader) {
				cerr << "ERROR: Subscriber::main(): reader is nil." << endl;
				return -1;
			}
			cout << "Successfully subscribed to: " << *i << endl;
		}
		//loop until the user demands to quit
		string end;
		while (true) {
			cout << "TO QUIT PRESS X" << endl;
			getline(cin, end);
			if (user == "X") {
				break;
			}
		}
		// Clean-up!
		participant->delete_contained_entities();
		dpf->delete_participant(participant);
		TheServiceParticipant->shutdown();
	}
	catch(const CORBA::Exception& e){
		e._tao_print_exception("Exception caught in Subscriber::main():");
		return -1;
	}
	return 0;
}