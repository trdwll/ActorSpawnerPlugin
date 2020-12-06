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
        bat "py C:\\jenkins.py ActorSpawnerPlugin Build \"%WORKSPACE%\""
      }
    }

    stage('Publish') {
      when {
        branch "main"
      }
      steps {
        bat "py C:\\jenkins.py ActorSpawnerPlugin Publish \"%WORKSPACE%\""
      }
    }
  }
}
