pipeline {
  options {
        disableConcurrentBuilds()
    }
  agent {
    node {
      label 'Windows'
      customWorkspace 'ActorSpawnerPlugin/ActorSpawnerPlugin'
    }

  }
  stages {
    stage('Build') {
      steps {
        bat 'C:\\build-scripts/ActorSpawnerPlugin/build.bat'
      }
    }

  }
}