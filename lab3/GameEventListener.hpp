class GameEventListener {
public:
    virtual ~GameEventListener() = default;
    // virtual void onChangeStateCondition() = 0;
    virtual void onGameOver() = 0;
    virtual void onStartGame() = 0;

};


// class Subject {
// public:
//     virtual ~Subject() {}
//     virtual void attach(Observer* observer) = 0;
//     virtual void detach(Observer* observer) = 0;
//     virtual void notify() = 0;
// };

// // Observer class
// class Observer {
// public:
//     virtual ~Observer() {}
//     virtual void update() = 0;
// };
