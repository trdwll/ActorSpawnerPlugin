pipeline {
  options {
        disableConcurrentBuilds()
    }
  agent {
    node {
      label 'Windows'
    }
  }
  stages {
    stage('Build') {
      steps {
        bat "C:\\JenkinsBuilder.exe ActorSpawnerPlugin Build \"%WORKSPACE%\""
      }
    }

    stage('Publish') {
      when {
        branch "main"
      }
      steps {
        bat "C:\\JenkinsBuilder.exe ActorSpawnerPlugin Publish \"%WORKSPACE%\""
      }
    }
  }
}
