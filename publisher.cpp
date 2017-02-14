/*
 *Local win32 Twitter Publisher
 *Author: Loay ASHMAWY
 *Company: Celad
*/
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <iostream>
#include "dds/DCPS/StaticIncludes.h"
#include "TwitterTypeSupportImpl.h"

const char* TYPE_NAME = "tweet";
DDS::DomainId_t TWITTER_DOMAIN_ID = 1500;

using namespace std;

int main (int argc, char *argv[]){
	cout << "Initializing Twitter for the publisher..." << endl;
	string user;
	if (argc < 3) {
		cerr << "ERROR: Publisher::main(): Usage Error, correct use -> publisher.exe -DCPSConfigFile rtps.ini" << endl;
		return -1;
	}
	cout << "Please enter your username: ";
	getline(cin, user);
	const char* username = user.c_str();
	
	try {
		// Initialize DomainParticipantFactory
		DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);

		// Create DomainParticipant
		DDS::DomainParticipant_var participant = dpf->create_participant(TWITTER_DOMAIN_ID, PARTICIPANT_QOS_DEFAULT, 0,OpenDDS::DCPS::DEFAULT_STATUS_MASK);

		if (!participant) {
			cerr << "ERROR: Publisher::main(): failed to create participant" << endl;
			return -1;
		}

		// Register TypeSupport (Twitter::Tweet)
		Twitter::TweetTypeSupport_var ts= new Twitter::TweetTypeSupportImpl;
		if (ts->register_type(participant, TYPE_NAME) != DDS::RETCODE_OK) {
			cerr << "ERROR: Publisher: main(): failed to register_type" << TYPE_NAME << endl;
			return -1;
		}

		//Create topic associated to the user
		DDS::Topic_var topic = participant->create_topic(username, TYPE_NAME, TOPIC_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		if (!topic) {
			cerr << "ERROR: Publisher::main(): failed to create topic" << endl;
			return -1;
		}

		// Create Publisher
		DDS::Publisher_var publisher = participant->create_publisher(PUBLISHER_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		if (!publisher) {
			cerr << "ERROR: Publisher::main(): failed to create publisher" << endl;
			return -1;
		}

		// Create DataWriter
		DDS::DataWriter_var writer_base = publisher->create_datawriter(topic, DATAWRITER_QOS_DEFAULT, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		if (!writer_base) {
			cerr << "ERROR: Publisher::main(): failed to create base writer" << endl;
			return -1;
		}
		//narrow to our message type
		Twitter::TweetDataWriter_var writer = Twitter::TweetDataWriter::_narrow(writer_base);
		if (!writer) {
			cerr << "ERROR: Publisher::main(): failed to create writer" << endl;
			return -1;
		}
		cout << "********************************************************" << endl;
		cout << "*                    Hello Twitter                     *" << endl;
		cout << "********************************************************" << endl;
		//Write tweets
		Twitter::Tweet tweet;
		tweet.count = 0;
		tweet.owner = username;
		cout << "Hello " << username << ". You can begin to tweet!" << endl;
		string text;
		while (true)
		{
			cout << "Please write your tweet number " << tweet.count + 1 << ". To exit press X: " << endl;
			getline(cin, text);
			if (text == "X") {
				cout << "Quitting Twitter..." << endl;
				break;
			}
			tweet.count++;
			tweet.text = text.c_str();
			DDS::ReturnCode_t error = writer->write(tweet, DDS::HANDLE_NIL);
			if (error != DDS::RETCODE_OK) {
				cerr << "ERROR: Publisher::main(): Unable to post tweet" << endl;
				return -1;
			}
		}

		// Clean-up!
		participant->delete_contained_entities();
		dpf->delete_participant(participant);
		TheServiceParticipant->shutdown();
	}
	catch (const CORBA::Exception& e) {
		e._tao_print_exception("Exception caught in Publisher::main():");
		return -1;
	}
	cout << "********************************************************" << endl;
	cout << "*                     Bye Twitter!                     *" << endl;
	cout << "********************************************************" << endl;
	return 0;
	
}