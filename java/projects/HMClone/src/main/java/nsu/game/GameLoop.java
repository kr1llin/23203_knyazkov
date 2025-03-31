package nsu.game;

public class GameLoop implements Runnable{

    private Game game;

    private boolean running;
    private final double updateRate = 1.0d / 60.0d; // slice

    public GameLoop(Game game){
        this.game = game;
    }

    @Override
    public void run(){
        running = true;
        double accumulator = 0; // keeps a track of a time that takes to update
        long currentTime, lastUpdate = System.currentTimeMillis();

        while(running) {
            currentTime = System.currentTimeMillis();
            double lastRenderTimeInSeconds = (currentTime - lastUpdate) / 1000d;
            accumulator += lastRenderTimeInSeconds;
            lastUpdate = currentTime;

            // to be sure it's updating in fixed intervals
            if (accumulator >= updateRate) {

                // 60 times per second update
                while (accumulator >= updateRate) {
                    update();
                    accumulator -= updateRate;
                }
            render();
            }
        }
    }

    private void update() {
        game.update();
    }
    private void render(){
        game.render();
    }
}
