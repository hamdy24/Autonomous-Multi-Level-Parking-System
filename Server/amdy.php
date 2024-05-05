<?php
$host = 'localhost';
$username = 'root';
$password = 'jinroot';
$database = 'amdyyy';

// Create a new MySQL connection
$conn = new mysqli($host, $username, $password, $database);
// Check for connection errors pain
if ($conn->connect_error) {
    die('Connection failed: ' . $conn->connect_error);
    writeLog('Connection to database failed');

}

$logFile = fopen('amdy_log.txt', 'a');
$logFile = 'amdy_log.txt';
/////////////////////////////////////////////////////////////////////////////////////
// Assume $conn is your database connection object

// Define the API endpoints
if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    if (isset($_GET['action'])) {
        switch ($_GET['action'] ) {

        }
    }
} elseif ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (isset($_POST['action'])) {
        switch ($_POST['action']) {

            case 'update_robot1':
                if (empty($_POST['robot1_state']) || empty($_POST['version'])) {
                    writeLog("Missing one or more parameters for robot1 update. Robot1 State: $robot1_state");
                    header('Content-Type: application/json');
                    echo json_encode(array('error' => 'Missing one or more parameters for robot1 update'));
                    exit();
                }
            
                $robot1_state = $_POST['robot1_state'];
                $version = $_POST['version'];
            
                // Update data in the 'robot1' table where id = 1
                $updateQuery = "UPDATE robot1 SET robot1_state = '$robot1_state', version = '$version' WHERE id = 1";
                $updateResult = $conn->query($updateQuery);
            
                if (!$updateResult) {
                    writeLog("Failed to update data in the 'robot1' table. Robot1 State: $robot1_state, Version: $version");
                    header('Content-Type: application/json');
                    echo json_encode(array('error' => 'Database query failed for robot1 update'));
                    exit();
                }
            
                writeLog("Data updated successfully in the 'robot1' table. Robot1 State: $robot1_state, Version: $version");
                header('Content-Type: application/json');
                echo json_encode(array('message' => 'Data updated successfully in the "robot1" table'));
                break;
        
            case 'update_robot2':
                if (empty($_POST['robot2_state']) || empty($_POST['version'])) {
                    writeLog("Missing one or more parameters for robot2 update. Robot2 State: $robot2_state");
                    header('Content-Type: application/json');
                    echo json_encode(array('error' => 'Missing one or more parameters for robot2 update'));
                    exit();
                }
            
                $robot2_state = $_POST['robot2_state'];
                $version = $_POST['version'];
            
                // Update data in the 'robot2' table where id = 1
                $updateQuery = "UPDATE robot1 SET robot2_state = '$robot2_state', version = '$version' WHERE id = 1";
                $updateResult = $conn->query($updateQuery);
            
                if (!$updateResult) {
                    writeLog("Failed to update data in the 'robot2' table. Robot2 State: $robot2_state, Version: $version");
                    header('Content-Type: application/json');
                    echo json_encode(array('error' => 'Database query failed for robot2 update'));
                    exit();
                }
            
                writeLog("Data updated successfully in the 'robot2' table. Robot2 State: $robot2_state, Version: $version");
                header('Content-Type: application/json');
                echo json_encode(array('message' => 'Data updated successfully in the "robot2" table'));
                break;          
/////////////////////////////////////////////////////////////////////////////////////////
                case 'get_data':
                    // Inside the 'get_data' action
                    $getDataQuery = "SELECT * FROM robot1 WHERE id = 1";
                    $getDataResult = $conn->query($getDataQuery);
    
                    if (!$getDataResult) {
                        writeLog("Failed to retrieve data from the 'robot1' table.");
                        header('Content-Type: application/json');
                        echo json_encode(array('error' => 'Database query failed'));
                        exit();
                    }
    
                    $row = $getDataResult->fetch_assoc();
                    writeLog("Data retrieved successfully from the 'robot1' table. Robot1 State: {$row['robot1_state']}, Robot2 State: {$row['robot2_state']}, Version: {$row['version']}");
                    header('Content-Type: application/json');
                    echo json_encode($row);
                    break;
        }
    }
}

// Function to write log data (adjust this according to your log system)
function writeLog($message) {
    global $logFile;
    $timestamp = date('Y-m-d H:i:s');
    $logMessage = $timestamp . ' - ' . $message . PHP_EOL;
    file_put_contents($logFile, $logMessage, FILE_APPEND);
}
