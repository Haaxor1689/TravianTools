#ifndef MACROS_HPP
#define MACROS_HPP

// AppConfigs macros
#define GroupStart(Name) struct Name { Name() = delete;
#define Add(Type, Name, Value) \
	private: \
	    static Type& raw##Name() { static Type data = Value; return data; } \
	public: \
	    static const Type& Name() { return raw##Name##(); } \
	    static void set##Name(Type newValue) { raw##Name() = newValue; }

#define AddConst(Type, Name, Value) \
	public: \
	    static Type Name() { return Value; } \

#define GroupEnd };

// QButton macros
#define AddButton(Name) private: QPushButton* Name; \
	                    private Q_SLOTS: void Name##Tapped();

#define ConstructButton(Name, Text) Name = new QPushButton(Text, this);\
	                                QObject::connect(Name, SIGNAL (released()), this, SLOT (Name##Tapped()));

// Connect macros
#define ConnectPair(Sender, Reciever, Method) \
	QObject::connect(Sender, SIGNAL(Method), Reciever, SLOT(Method));

#endif // MACROS_HPP
