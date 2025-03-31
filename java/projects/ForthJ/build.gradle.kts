plugins {
    id("java")
    application
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

java {
    toolchain {
        languageVersion = JavaLanguageVersion.of(23)
    }
}


dependencies {
    testImplementation(platform("org.junit:junit-bom:5.12.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    testImplementation("org.mockito:mockito-core:5.4.0")
    testImplementation("org.mockito:mockito-junit-jupiter:5.4.0")
    testRuntimeOnly("org.junit.platform:junit-platform-launcher")
    implementation (platform("org.apache.logging.log4j:log4j-bom:2.24.3"))
    implementation ("org.apache.logging.log4j:log4j-api:2.24.3")

    runtimeOnly ("org.apache.logging.log4j:log4j-core")
    runtimeOnly ("org.apache.logging.log4j:log4j-layout-template-json")
}

tasks.test {
    useJUnitPlatform()
}

application{
    mainClass.set("forth.Main")
}