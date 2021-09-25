FROM java:8
MAINTAINER zyx
ADD cps-0.0.1-SNAPSHOT.jar cps.jar
EXPOSE 2000
ENTRYPOINT ["java","-jar","-Duser.timezone=GMT+8","cps.jar"]