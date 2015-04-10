#ifndef MESSAGE_H
#define MESSAGE_H

class Message {
public:
	Message(const Message & msg);
	void SetTime(time_t update);
	void SetSeq(int32_t seq);
};

#endif // MESSAGE_H

