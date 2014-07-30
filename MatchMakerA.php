<?php

    class MatchMakerA {

        public $criteria;
        public $SNum;
        public $PNum;

        public function __construct($iCriteria, $iSNum, $iPNum) {
            echo "In default constructor\n";
            $this->criteria = $iCriteria;
            $this->SNum = $iSNum;
            $this->PNum = $iPNum;
        }

        public function StudentSize(& $Student, $SNum, $criteria) {
            echo "called StudentSize\n";

            for ($i = 0; $i < $SNum; $i++)  {
                $ti = $i + 1;
                echo "Student Number: ".$ti."\n";
                for ($j = 0; $j < $criteria; $j++) {
                    $Student[$i][$j] = rand(0, 10);
                    echo "".$Student[$i][$j]." ";
                }
                echo "\n";
            }
        }

        public function ProjectSize(& $Project, $PNum, $criteria) {
            echo "called ProjectSize\n";

            for ($i = 0; $i < $PNum; $i++) {
                $ti = $i + 1;
                echo "Project Number: ".$ti."\n";
                for ($j = 0; $j < $criteria; $j++) {
                    $Project[$i][$j] = rand(0, 10);
                    echo "".$Project[$i][$j]." ";
                }
                echo "\n";
            }
        }

        public function RegionDivide(& $region, & $reqNum, $criteria) {
            echo "called RegionDivide\n";
            $skillNum; $placeHolder; $sum = 0; $code = 0; $x;

            //less than th eohter values
            echo "Enter the number of skill regions (Default 5): "
            $skillNum = 5;

            $region[0] = $skillNum;

            do {
                for ($x = 0; $x < $skillNum; $x++) {
                    $tx = $x + 1;
                    echo "Enter requirements in region ".$tx."(def is 4): ";
                    $placeHolder = 4;
                    $sum += $placeHolder;

                    if ($sum > $criteria) {
                        echo "not enough criteria";
                        $sum = 0;
                        break;
                    } else if ($sum == $criteria) {

                    }
                }


            } while ($code == 0);


        }

        public function FindArea($index, $criteria) {
            echo "called FindArea\n";
        }

        public function SumArea() {
            echo "called SumArea\n";
        }

        public function Compare() {
            echo "called Compare\n";
        }

        public function RegionAnalyze() {
            echo "called RegionAnalyze\n";
        }

        public function RegionSum() {
            echo "called RegionSum\n";
        }

        public function RegionCompare() {
            echo "called RegionCompare\n";
        }

        public function TotalSize() {
            echo "called TotalSize\n";
        }

        public function RegDiffSize() {
            echo "called RegDiffSize\n";
        }

        public function AreaSize() {
            echo "called AreaSize\n";
        }

        public function DiffSize() {
            echo "called DiffSize\n";
        }
    }

    $criteria = 12;
    $SNum = 12;
    $PNum = 15;

    $MMO = new MatchMakerA($criteria, $SNum, $PNum);

    $Student = array(array());
    $Project = array(array());
    $region = array();
    $reqNum = array();

    $MMO->StudentSize($Student, $MMO->SNum, $MMO->criteria);
    $MMO->ProjectSize($Project, $MMO->PNum, $MMO->criteria);

    $MMO->RegionDivide($region, $reqNum, $MMO->criteria);
?>
