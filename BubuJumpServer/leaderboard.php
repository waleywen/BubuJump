<?php
    if (!defined("SAE_MYSQL_USER"))
    {
        define("SAE_MYSQL_USER", "bubujump");
        define("SAE_MYSQL_PASS", "123456");
        define("SAE_MYSQL_HOST_M", "localhost");
        define("SAE_MYSQL_PORT", "3306");
        define("SAE_MYSQL_DB", "bubujump");
    }
    
    class Record
    {
        var $id;
        var $name;
        var $score;
    }
    
    $clientSum = '';
    if (isset($_GET['sum']))
    {
        $clientSum = $_GET['sum'];
    }
    else
    {
        die('{"error":"0"}');
    }
    
    $sumKey = '1234567890';
    $md5Sum = $sumKey;
    
    $type = '';
    if (isset($_GET['type']))
    {
        $type = $_GET['type'];
        $md5Sum .= $type;
    }
    else
    {
        die('{"error":"1"}');
    }
    
    if ("0" == $type)
    {
        $id = '';
        if (isset($_GET['id']))
        {
            $id = $_GET['id'];
            $md5Sum .= $id;
        }

        if (md5($md5Sum) == $clientSum)
//      if (md5($md5Sum) != $clientSum)
        {
            $conn = mysql_connect(SAE_MYSQL_HOST_M.':'.SAE_MYSQL_PORT, SAE_MYSQL_USER, SAE_MYSQL_PASS);
            mysql_select_db(SAE_MYSQL_DB, $conn);
            
            $resultArray = array();
            $rows = array();

            $result1 = mysql_query("SELECT * FROM leaderboard ORDER BY score DESC LIMIT 50");
            while($row = mysql_fetch_object($result1))
            {
                $record = new Record();
                $record->id = (int)$row->id;
                $record->name = $row->name;
                $record->score = (int)$row->score;
                array_push($rows, $record);
            }
            mysql_free_result($result1);
            
            if ('' == $id || 0 > $id )
            {
                $place = 0;
                $id = -1;
                $score = 0;
            }
            else
            {
                $result2 = mysql_query("SELECT score FROM `leaderboard` WHERE `id` = ".$id);
                $numRows = mysql_num_rows($result2);
                if (1 != $numRows)
                {
                    $id = -1;
                    $score = 0;
                }
                else
                {
                    $row = mysql_fetch_row($result2);
                    $score = $row[0];
                }
                mysql_free_result($result2);
                
                $result3 = mysql_query("SELECT count(*) AS count FROM `leaderboard` WHERE score > ".$score);
                $row = mysql_fetch_row($result3);
                $place = (int)($row[0] + 1);
                mysql_free_result($result3);
                
            }
            $resultArray['sameScorePlace'] = $place;
            $resultArray['myID'] = (int)$id;
            $resultArray['myScore'] = (int)$score;
            $resultArray['leaderboard'] = $rows;

            echo json_encode($resultArray);
            
            mysql_close($conn);
        }
        else
        {
            die('{"error":"-1"}');
        }
    }
    else
    {
        $id = '';
        $name = '';
        $score = 0;
        $lotteryID = -1;
        
        if (isset($_GET['id']))
        {
            $id = $_GET['id'];
            $md5Sum .= $id;
        }
        if (isset($_GET['name']))
        {
            $name = $_GET['name'];
            $md5Sum .= $_GET['name'];
        }
        if (isset($_GET['score']))
        {
            $score = $_GET['score'];
            $md5Sum .= $_GET['score'];
        }
        else
        {
            die('{"error":"2"}');
        }
        if (isset($_GET['lottery_id']))
        {
            $lotteryID = $_GET['lottery_id'];
            $md5Sum .= $_GET['lottery_id'];
        }

        if (md5($md5Sum) == $clientSum)
//      if (md5($md5Sum) != $clientSum)
        {
            $conn = mysql_connect(SAE_MYSQL_HOST_M.':'.SAE_MYSQL_PORT, SAE_MYSQL_USER, SAE_MYSQL_PASS);
            mysql_select_db(SAE_MYSQL_DB, $conn);
            
            if ('' != $id)
            {
                $findIDResult = mysql_query("SELECT name, lottery_id FROM `leaderboard` WHERE id = ".$id);
                $numRows = mysql_num_rows($findIDResult);
                if (1 != $numRows)
                {
                    $id = '';
                }
                else
                {
                    $row = mysql_fetch_row($findIDResult);
                    $oldName = $row[0];
                    $oldLotteryID = $row[1];
                    if ($name != $oldName || $lotteryID != $oldLotteryID)
                    {
                        mysql_query("UPDATE leaderboard SET name = '".$name."', lottery_id = ".$lotteryID." WHERE id = ".$id);
                    }
                }
                mysql_free_result($findIDResult);
            }
            
            if ('' != $id)
            {
                //Update
                $updated = mysql_query("UPDATE leaderboard SET score = ".$score." WHERE id = ".$id." and score < ".$score);
                if (0 != $updated && mysql_affected_rows() == 0)
                {
                    $currentScoreResult = mysql_query("SELECT score AS count FROM `leaderboard` WHERE id = ".$id);
                    $row = mysql_fetch_row($currentScoreResult);
                    $score = $row[0];
                    mysql_free_result($currentScoreResult);
                }
            }
            else
            {
                //Insert
                mysql_query("INSERT INTO leaderboard (name, score, lottery_id) VALUES ('".$name."', ".$score.", ".$lotteryID.")");
                $id = mysql_insert_id();
            }
            
            $resultArray = array();
            $rows = array();
            
            $result1 = mysql_query("SELECT * FROM leaderboard WHERE score > ".$score." ORDER BY score LIMIT 10");
            while($row = mysql_fetch_object($result1))
            {
                $record = new Record();
                $record->id = (int)$row->id;
                $record->name = $row->name;
                $record->score = (int)$row->score;
                array_push($rows, $record);
            }
            mysql_free_result($result1);
            
            $rows = array_reverse($rows);
            
            $result2 = mysql_query("SELECT * FROM leaderboard WHERE score = ".$score);
            while($row = mysql_fetch_object($result2))
            {
                $record = new Record();
                $record->id = (int)$row->id;
                $record->name = $row->name;
                $record->score = (int)$row->score;
                array_push($rows, $record);
            }
            mysql_free_result($result2);
            
            $result3 = mysql_query("SELECT * FROM leaderboard WHERE score < ".$score." ORDER BY score DESC LIMIT 10");
            while($row = mysql_fetch_object($result3))
            {
                $record = new Record();
                $record->id = (int)$row->id;
                $record->name = $row->name;
                $record->score = (int)$row->score;
                array_push($rows, $record);
            }
            mysql_free_result($result3);
            
            $result4 = mysql_query("SELECT count(*) AS count FROM `leaderboard` WHERE score > ".$score);
            $row = mysql_fetch_row($result4);
            $resultArray['sameScorePlace'] = (int)($row[0] + 1);
            mysql_free_result($result4);
            
            $resultArray['myID'] = (int)$id;
            $resultArray['myScore'] = (int)$score;
            $resultArray['leaderboard'] = $rows;
            
            echo json_encode($resultArray);
            
            mysql_close($conn);
        }
        else
        {
            die('{"error":"-1"}');
        }
    }
?>