<?php
    if (!defined("SAE_MYSQL_USER"))
    {
        define("SAE_MYSQL_USER", "bubujump");
        define("SAE_MYSQL_PASS", "123456");
        define("SAE_MYSQL_HOST_M", "localhost");
        define("SAE_MYSQL_PORT", "3306");
        define("SAE_MYSQL_DB", "bubujump");
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
    
    $id = '';
    $name = '';
    $phone = '';
    
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
    else
    {
        die('{"error":"1"}');
    }
    if (isset($_GET['phone']))
    {
        $phone = $_GET['phone'];
        $md5Sum .= $_GET['phone'];
    }
    else
    {
        die('{"error":"2"}');
    }
    
    if (md5($md5Sum) == $clientSum)
//    if (md5($md5Sum) != $clientSum)
    {
        $conn = mysql_connect(SAE_MYSQL_HOST_M.':'.SAE_MYSQL_PORT, SAE_MYSQL_USER, SAE_MYSQL_PASS);
        mysql_select_db(SAE_MYSQL_DB, $conn);
        
        if ('' != $id)
        {
            $findIDResult = mysql_query("SELECT * FROM `lottery` WHERE id = ".$id);
            $numRows = mysql_num_rows($findIDResult);
            if (1 != $numRows)
            {
                $id = '';
            }
            mysql_free_result($findIDResult);
        }
        
        if ('' != $id)
        {
            //Update
            $updated = mysql_query("UPDATE lottery SET name = ".$name.", phone = '".$phone."' WHERE id = ".$id);
        }
        else
        {
            //Insert
            mysql_query("INSERT INTO lottery (name, phone) VALUES ('".$name."', '".$phone."')");
            $id = mysql_insert_id();
        }
        
        $resultArray = array();
        $resultArray['myID'] = (int)$id;
        $resultArray['name'] = $name;
        $resultArray['phone'] = $phone;
        
        echo json_encode($resultArray);
        
        mysql_close($conn);
    }
    else
    {
        die('{"error":"-1"}');
    }
?>