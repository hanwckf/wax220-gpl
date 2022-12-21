
//var bwxhr = new XHR();

var G;
var TIME = 0;
var L01   = 1;
var L05   = 2;
var L15  = 3;

var width  = 760;
var height = 300;
var step   = 5;

var data_wanted = Math.floor(width / step);
var data_fill   = 0;
var data_stamp  = 0;

var data_01  = [ ];
var data_05  = [ ];
var data_15 = [ ];

var line_01;
var line_05;
var line_15;

var label_25;
var label_050;
var label_75;

var label_01_cur;
var label_01_avg;
var label_01_peak;

var label_05_cur;
var label_05_avg;
var label_05_peak;

var label_15_cur;
var label_15_avg;
var label_15_peak;

var label_scale;
var firstInterval;
var flag = 1;
function limitShow(n)
{
	return (n >= 100) ? 100 : n ;
}

function cpuLoad()
{
	data1 = {anticsrf: '<% generateToken("cpu_load") %>', submitType:"cpu_load", load:flag};

			ajax_normal({
				async: false,
				type : "POST",
				url: '<% action_url("apply.cgi", "load.htm") %>',
				data:data1,
				dataType:"json",
				error:function(){
					//console.log("wifi_Channel error");
				},
				success:function(data){

				//function(x, data)
				//{
					var data_max   = 0;
					var data_scale = 0;
					var data_tmp = 0;

					var data_01_avg = 0;
					var data_05_avg = 0;
					var data_15_avg = 0;

					var data_01_peak = 0;
					var data_05_peak = 0;
					var data_15_peak = 0;

					for (var i = data_stamp ? 0 : 1; i < data.length; i++)
					{
						/* skip overlapping entries */
						if (data[i].time_tmp <= data_stamp)
							continue;

						data_tmp = parseInt(100 - data[i].cpu_used);
						if (isNaN(data_tmp))
							continue;
						data_01.push(data_tmp);
						//data_05.push(data[i][L05]);
						//data_15.push(data[i][L15]);
					}

					/* cut off outdated entries */
					data_01 = data_01.slice(data_01.length - data_wanted, data_01.length);
					//data_05 = data_05.slice(data_05.length - data_wanted, data_05.length);
					//data_15 = data_15.slice(data_15.length - data_wanted, data_15.length);

					/* find peak */
					for (var i = 0; i < data_01.length; i++)
					{
						data_max = Math.max(data_max, data_01[i]);
						//data_max = Math.max(data_max, data_05[i]);
						//data_max = Math.max(data_max, data_15[i]);

						data_01_peak = Math.max(data_01_peak, data_01[i]);
						//data_05_peak = Math.max(data_05_peak, data_05[i]);
						//data_15_peak = Math.max(data_15_peak, data_15[i]);

						if (i > 0)
						{
							data_01_avg = (data_01_avg + data_01[i]) / 2;
							//data_05_avg = (data_05_avg + data_05[i]) / 2;
							//data_15_avg = (data_15_avg + data_15[i]) / 2;
						}
						else
						{
							data_01_avg = data_01[i];
							//data_05_avg = data_05[i];
							//data_15_avg = data_15[i];
						}
					}

					/* remember current timestamp, calculate horizontal scale */
					if(data[data.length-1])
					{
						data_stamp = data[data.length-1].time_tmp;
					}

					if (data_max != 0)
					{
						data_scale = height / (data_max * 1.1);
					}

					//<%#reverse array for line from left to right%>
					data_01.reverse();
					//data_05.reverse();
					//data_15.reverse();

					/* plot data */
					var pt_01 = '0,' + height;
					//var pt_05 = '0,' + height;
					//var pt_15 = '0,' + height;

					var y_01 = 0;
					//var y_05 = 0;
					//var y_15 = 0;

					for (var i = 0; i < data_01.length; i++)
					{
						var x = i * step;

						y_01 = height - Math.floor(data_01[i] * data_scale);
						//y_05 = height - Math.floor(data_05[i] * data_scale);
						//y_15 = height - Math.floor(data_15[i] * data_scale);

						pt_01 += ' ' + x + ',' + y_01;
						//pt_05 += ' ' + x + ',' + y_05;
						//pt_15 += ' ' + x + ',' + y_15;
					}

					pt_01 += ' ' + width + ',' + y_01 + ' ' + width + ',' + height;
					//pt_05 += ' ' + width + ',' + y_05 + ' ' + width + ',' + height;
					//pt_15 += ' ' + width + ',' + y_15 + ' ' + width + ',' + height;


					line_01.setAttribute('points', pt_01);
					line_01.setAttribute('style', 'fill:none;stroke:#ff0000;stroke-width:1;');
					/*
					line_05.setAttribute('points', pt_05);
					line_05.setAttribute('style', 'fill:none;stroke:#ff6600;stroke-width:1;');
					line_15.setAttribute('points', pt_15);
					line_15.setAttribute('style', 'fill:none;stroke:#ffaa00;stroke-width:1;');
					*/

					//<%#reverse back to original order, because data poll needed.%>
					data_01.reverse();
					//data_05.reverse();
					//data_15.reverse();

					//<%#Y axle%>
					var v_top = (1.1 * 0.25 * data_max).toFixed();
					$$("#bwsvg").css("width",  (v_top >= 100)?"95%":"97%");
					
					$$("#label_25").html((1.1 * 0.25 * data_max).toFixed());
					$$("#label_50").html((1.1 * 0.50 * data_max).toFixed());
					$$("#label_75").html((1.1 * 0.75 * data_max).toFixed());

					label_01_cur.innerHTML = limitShow((data_01[data_01.length-1]).toFixed())+' %';
//						label_05_cur.innerHTML = limitShow((data_05[data_05.length-1]).toFixed())+' %';
//						label_15_cur.innerHTML = limitShow((data_15[data_15.length-1]).toFixed())+' %';

					label_01_avg.innerHTML = limitShow((data_01_avg).toFixed())+' %';
//						label_05_avg.innerHTML = limitShow((data_05_avg).toFixed())+' %';
//						label_15_avg.innerHTML = limitShow((data_15_avg).toFixed())+' %';

					label_01_peak.innerHTML = limitShow((data_01_peak).toFixed())+' %';
//						label_05_peak.innerHTML = limitShow((data_05_peak).toFixed())+' %';
//						label_15_peak.innerHTML = limitShow((data_15_peak).toFixed())+' %';
					}
				});

	if (firstInterval)
		clearInterval(firstInterval);

	flag = 0;
	firstInterval = setInterval("cpuLoad()", 3000);

}

	/* wait for SVG */
window.setTimeout(
	function() {
		var svg = document.getElementById('bwsvg');

		if(svg)
		{
			try {
				G = svg.getSVGDocument
					? svg.getSVGDocument() : svg.contentDocument;
			}
			catch(e) {
				G = document.embeds['bwsvg'].getSVGDocument();
			}
		}

		if (!G)
		{
			/* render datasets, start update interval */
			//XHR.poll(15, '<%=build_url("admin/status/realtime/load_status")%>', null,
			var data={};
				//function(x, data)
				{
					label_01_cur=document.getElementById('lb_load01_cur');
					label_01_avg=document.getElementById('lb_load01_avg');
					label_01_peak=document.getElementById('lb_load01_peak');
					label_05_cur=document.getElementById('lb_load05_cur');
					label_05_avg=document.getElementById('lb_load05_avg');
					label_05_peak=document.getElementById('lb_load05_peak');
					label_15_cur=document.getElementById('lb_load15_cur');
					label_15_avg=document.getElementById('lb_load15_avg');
					label_15_peak=document.getElementById('lb_load15_peak');
					
					var data_max   = 0;
					var data_scale = 0;

					var data_01_avg = 0;
					var data_05_avg = 0;
					var data_15_avg = 0;

					var data_01_peak = 0;
					var data_05_peak = 0;
					var data_15_peak = 0;

					if((data != null) && (data.length != null))
					{
						for(var i=data_stamp?0:1; i<data.length; i++)
						{
							/* skip overlapping entries */
							if(data[i].time_tmp<=data_stamp)
								continue;
							data_01.push(data[i].cpu_used);
//								data_05.push(data[i][L05]);
//								data_15.push(data[i][L15]);
						}
						/* cut off outdated entries */
						data_01=data_01.slice(data_01.length-data_wanted,data_01.length);
//							data_05=data_05.slice(data_05.length-data_wanted,data_05.length);
//							data_15=data_15.slice(data_15.length-data_wanted,data_15.length);
						/* find peak */
						for(var i=0; i<data_01.length; i++)
						{
							data_max=Math.max(data_max,data_01[i]);
//								data_max=Math.max(data_max,data_05[i]);
//								data_max=Math.max(data_max,data_15[i]);
							data_01_peak=Math.max(data_01_peak,data_01[i]);
//								data_05_peak=Math.max(data_05_peak,data_05[i]);
//								data_15_peak=Math.max(data_15_peak,data_15[i]);
							if(i>0)
							{
								data_01_avg=(data_01_avg+data_01[i])/2;
//									data_05_avg=(data_05_avg+data_05[i])/2;
//									data_15_avg=(data_15_avg+data_15[i])/2;
							}
							else
							{
								data_01_avg=data_01[i];
//									data_05_avg=data_05[i];
//									data_15_avg=data_15[i];
							}
						}
						/* remember current timestamp, calculate horizontal scale */
						if(data[data.length-1])
						{
							data_stamp=data[data.length-1][TIME];
						}

						label_01_cur.innerHTML = limitShow((data_01[data_01.length-1]).toFixed())+' %';
//							label_05_cur.innerHTML = limitShow((data_05[data_05.length-1]).toFixed())+' %';
//							label_15_cur.innerHTML = limitShow((data_15[data_15.length-1]).toFixed())+' %';

						label_01_avg.innerHTML = limitShow((data_01_avg).toFixed())+' %';
//							label_05_avg.innerHTML = limitShow((data_05_avg).toFixed())+' %';
//							label_15_avg.innerHTML = limitShow((data_15_avg).toFixed())+' %';

						label_01_peak.innerHTML = limitShow((data_01_peak).toFixed())+' %';
//							label_05_peak.innerHTML = limitShow((data_05_peak).toFixed())+' %';
//							label_15_peak.innerHTML = limitShow((data_15_peak).toFixed())+' %';
					}
				}
			//);
			
			window.setTimeout(arguments.callee, 1000);
		}
		else
		{
			/* find sizes */
			width       = svg.offsetWidth  - 2;
			height      = svg.offsetHeight - 2;
			data_wanted = Math.ceil(width / step);

			/* prefill datasets */
			for (var i = 0; i < data_wanted; i++)
			{
				data_01[i] = 0;
				//data_05[i] = 0;
				//data_15[i] = 0;
			}

			/* find svg elements */
			line_01 = G.getElementById('load01');
			line_05 = G.getElementById('load05');
			line_15 = G.getElementById('load15');

			label_25 = G.getElementById('label_25');
			label_50 = G.getElementById('label_50');
			label_75 = G.getElementById('label_75');

			label_01_cur  = document.getElementById('lb_load01_cur');
			label_01_avg  = document.getElementById('lb_load01_avg');
			label_01_peak = document.getElementById('lb_load01_peak');

			label_05_cur  = document.getElementById('lb_load05_cur');
			label_05_avg  = document.getElementById('lb_load05_avg');
			label_05_peak = document.getElementById('lb_load05_peak');

			label_15_cur  = document.getElementById('lb_load15_cur');
			label_15_avg  = document.getElementById('lb_load15_avg');
			label_15_peak = document.getElementById('lb_load15_peak');

			label_scale   = document.getElementById('scale');


			/* plot horizontal time interval lines */
			for (var i = width % (step * 60); i < width; i += step * 60)
			{
				var line = G.createElementNS('http://www.w3.org/2000/svg', 'line');
					line.setAttribute('x1', i);
					line.setAttribute('y1', 0);
					line.setAttribute('x2', i);
					line.setAttribute('y2', '100%');
					line.setAttribute('style', 'stroke:black;stroke-width:0.1');

				var text = G.createElementNS('http://www.w3.org/2000/svg', 'text');
					text.setAttribute('x', i + 5);
					text.setAttribute('y', 15);
					text.setAttribute('style', 'fill:#999999; font-size:9pt');
					text.appendChild(G.createTextNode(Math.round((width - i) / step / 60) + 'm'));

//					label_25.parentNode.appendChild(line);
//					label_25.parentNode.appendChild(text);
			}

			label_scale.innerHTML = String.format("$connection_info_1", Math.floor(data_wanted / 60), 3);

			/* render datasets, start update interval */
			//XHR.poll(3, '<%=build_url("admin/status/realtime/load_status")%>', null,
			//var data={};
			
			//);
			cpuLoad();
		}
	}, 1000
);


if($$.support.leadingWhitespace)
{
	//document.write('<div class="realtime_chart"><div id="label_25" class="label_75"></div><div id="label_50" class="label_50"></div><div id="label_75" class="label_25"></div><embed id="bwsvg" style="width:96%; height:300px; border:1px solid #000000; background-color:#FFFFFF" src="/image/load.svg" /> </div>');
}
