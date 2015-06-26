#!/usr/bin/perl

use strict;
use warnings;

my $i=0;
my $sum_tempo_quad=0;
my $sum_tempo_linear=0;
my $sum_mem_quad=0;
my $sum_mem_linear=0;
my $mem_peek=0;
my $mem_quad_or_linear='q';

while (<>) {
  if (m/i= (\d*), j=1/) {
    if ($i > 0) {
      printf "\n---------\n".
	"i= %d" . "\n".
	"tempo quad:   " . "%0.3f" . "\n".
	"tempo linear: " . "%0.3f" . "\n".
	"memoria quad:   " . "%d"  . "\n".
	"memoria linear: " . "%d"  . "\n",
	, $i , ($sum_tempo_quad / 10 ) * 1000  , ($sum_tempo_linear / 10) * 1000,
	$sum_mem_quad / 10 , $sum_mem_linear / 10;
      }
    $i=$1;
    $sum_tempo_quad=0;
    $sum_tempo_linear=0;
    $sum_mem_quad=0;
    $sum_mem_linear=0;
    next;
  }
  if (m/quadratico: tempo = (.*)/) {
    $sum_tempo_quad+=$1;
    $mem_quad_or_linear = 'l';
    next;
    
  }
  if (m/linear\s*: tempo = (.*)/) {
    $sum_tempo_linear+=$1;
    $mem_quad_or_linear = 'q';
    next;
  }
  if (m/\(current\): (.*)/) {
    if ($mem_quad_or_linear eq 'q') {
      $sum_mem_quad += $1
    }
    if ($mem_quad_or_linear eq 'l') {
      $sum_mem_linear += $1
    }
    next;
  }
}
