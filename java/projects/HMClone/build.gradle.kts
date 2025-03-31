plugins {
    id("java")
    id ("application")
    id ("org.openjfx.javafxplugin") version "0.1.0"
}

javafx {
    version = "23.0.2"
    modules = listOf("javafx.controls", "javafx.fxml", "javafx.media")
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
    jcenter()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    implementation("com.github.almasb:fxgl:21.1")
}

tasks.test {
    useJUnitPlatform()
}

application {
    mainClass.set("nsu.HMClone")
}