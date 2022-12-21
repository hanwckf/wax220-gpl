	var bwxhr = new XHR();

	var G, G2;
	var TIME  = 0;
	var RATE  = 1;
	var RSSI  = 2;
	var NOISE = 3;

	var width  = 760;
	var height = 300;
	var step   = 5;

	var data_wanted = Math.floor(width / step);
	var data_fill   = 0;
	var data_stamp  = 0;

	var data_rssi = [ ];
	var data_noise = [ ];
	var data_rate = [ ];

	var line_rssi;
	var line_noise;
	var line_rate;

	var label_25, label_25_2;
	var label_50, label_50_2;
	var label_75, label_75_2;

	var label_rssi_cur;
	var label_rssi_avg;
	var label_rssi_peak;

	var label_noise_cur;
	var label_noise_avg;
	var label_noise_peak;

	var label_rate_cur;
	var label_rate_avg;
	var label_rate_peak;

	var label_scale;


	/* wait for SVG */
	window.setTimeout(
		function() {
			var svg = document.getElementById('iwsvg');
			var svg2 = document.getElementById('iwsvg2');

			if(svg & svg2)
			{
				try
				{
					G=svg.getSVGDocument
							?svg.getSVGDocument():svg.contentDocument;
					G2=svg2.getSVGDocument
							?svg2.getSVGDocument():svg2.contentDocument;
				}
				catch (e)
				{
					G=document.embeds['iwsvg'].getSVGDocument();
					G2=document.embeds['iwsvg2'].getSVGDocument();
				}
			}

			if (!G || !G2)
			{
				/* render datasets, start update interval */
				XHR.poll(3, '<%=build_url("admin/status/realtime/wireless_status", curdev)%>', null,
					function(x, data)
					{
						label_rssi_cur=document.getElementById('rssi_bw_cur');
						label_rssi_avg=document.getElementById('rssi_bw_avg');
						label_rssi_peak=document.getElementById('rssi_bw_peak');
						label_noise_cur=document.getElementById('noise_bw_cur');
						label_noise_avg=document.getElementById('noise_bw_avg');
						label_noise_peak=document.getElementById('noise_bw_peak');
						label_rate_cur=document.getElementById('rate_bw_cur');
						label_rate_avg=document.getElementById('rate_bw_avg');
						label_rate_peak=document.getElementById('rate_bw_peak');
						
						var noise_floor = 255;
						var rate_floor = 60000;

						if((data != null) && (data.length != null))
						{
							for(var i=0; i<data.length; i++)
							{
								noise_floor=Math.min(noise_floor,data[i][NOISE]);
								rate_floor=Math.min(rate_floor,data[i][RATE]);
							}
							noise_floor-=5;
							var data_max=0;
							var data_scale=0;
							var data_max_2=0;
							var data_scale_2=0;
							var data_rssi_avg=0;
							var data_noise_avg=0;
							var data_rate_avg=0;
							var data_rssi_peak=0;
							var data_noise_peak=0;
							var data_rate_peak=0;
							for(var i=data_stamp?0:1; i<data.length; i++)
							{
								/* skip overlapping entries */
								if(data[i][TIME]<=data_stamp)
									continue;
								data_rssi.push(data[i][RSSI]-noise_floor);
								data_noise.push(data[i][NOISE]-noise_floor);
								data_rate.push(Math.floor(data[i][RATE]/1000));
							}
							/* cut off outdated entries */
							data_rssi=data_rssi.slice(data_rssi.length-data_wanted,data_rssi.length);
							data_noise=data_noise.slice(data_noise.length-data_wanted,data_noise.length);
							data_rate=data_rate.slice(data_rate.length-data_wanted,data_rate.length);
							/* find peak */
							for(var i=0; i<data_rssi.length; i++)
							{
								data_max=Math.max(data_max,data_rssi[i]);
								data_max_2=Math.max(data_max_2,data_rate[i]);
								data_rssi_peak=Math.max(data_rssi_peak,data_rssi[i]);
								data_noise_peak=Math.max(data_noise_peak,data_noise[i]);
								data_rate_peak=Math.max(data_rate_peak,data_rate[i]);
								if(i>0)
								{
									data_rssi_avg=(data_rssi_avg+data_rssi[i])/2;
									data_noise_avg=(data_noise_avg+data_noise[i])/2;
									data_rate_avg=(data_rate_avg+data_rate[i])/2;
								}
								else
								{
									data_rssi_avg=data_rssi[i];
									data_noise_avg=data_noise[i];
									data_rate_avg=data_rate[i];
								}
							}
							/* remember current timestamp, calculate horizontal scale */
							data_stamp=data[data.length-1][TIME];
							data_scale=(height/(data_max*1.1)).toFixed(1);
							data_scale_2=(height/(data_max_2*1.1)).toFixed(1);
							/* plot data */
							var pt_rssi='0,'+height;
							var pt_noise='0,'+height;
							var pt_rate='0,'+height;
							var y_rssi=0;
							var y_noise=0;
							var y_rate=0;
							for(var i=0; i<data_rssi.length; i++)
							{
								var x=i*step;
								y_rssi=height-Math.floor(data_rssi[i]*data_scale);
								y_noise=height-Math.floor(data_noise[i]*data_scale);
								y_rate=height-Math.floor(data_rate[i]*data_scale_2);
								y_rssi-=Math.floor(y_rssi%(1/data_scale));
								y_noise-=Math.floor(y_noise%(1/data_scale));
								pt_rssi+=' '+x+','+y_rssi;
								pt_noise+=' '+x+','+y_noise;
								pt_rate+=' '+x+','+y_rate;
							}
							function wireless_label(dbm,noise)
							{
								if(noise)
									return String.format("%d <%:dBm%> (SNR %d <%:dBm%>)",noise_floor+dbm-255,dbm-noise);
								else
									return String.format("%d <%:dBm%>",noise_floor+dbm-255);
							}

							function rate_label(mbit)
							{
								return String.format("%d <%:Mbit/s%>",mbit);
							}

							label_rssi_cur.innerHTML=wireless_label(data_rssi[data_rssi.length-1],data_noise[data_noise.length-1]).nobr();
							label_noise_cur.innerHTML=wireless_label(data_noise[data_noise.length-1]).nobr();
							label_rssi_avg.innerHTML=wireless_label(data_rssi_avg,data_noise_avg).nobr();
							label_noise_avg.innerHTML=wireless_label(data_noise_avg).nobr();
							label_rssi_peak.innerHTML=wireless_label(data_rssi_peak,data_noise_peak).nobr();
							label_noise_peak.innerHTML=wireless_label(data_noise_peak).nobr();
							label_rate_cur.innerHTML=rate_label(data_rate[data_rate.length-1]);
							label_rate_avg.innerHTML=rate_label(data_rate_avg);
							label_rate_peak.innerHTML=rate_label(data_rate_peak);
						}
					}
				);
				
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
					data_rssi[i] = 0;
					data_noise[i] = 0;
					data_rate[i] = 0;
				}

				/* find svg elements */
				line_rssi = G.getElementById('rssi');
				line_noise = G.getElementById('noise');
				line_rate = G2.getElementById('rate');

				label_25 = G.getElementById('label_25');
				label_50 = G.getElementById('label_50');
				label_75 = G.getElementById('label_75');
				label_25_2 = G2.getElementById('label_25');
				label_50_2 = G2.getElementById('label_50');
				label_75_2 = G2.getElementById('label_75');

				label_rssi_cur  = document.getElementById('rssi_bw_cur');
				label_rssi_avg  = document.getElementById('rssi_bw_avg');
				label_rssi_peak = document.getElementById('rssi_bw_peak');

				label_noise_cur  = document.getElementById('noise_bw_cur');
				label_noise_avg  = document.getElementById('noise_bw_avg');
				label_noise_peak = document.getElementById('noise_bw_peak');

				label_rate_cur  = document.getElementById('rate_bw_cur');
				label_rate_avg  = document.getElementById('rate_bw_avg');
				label_rate_peak = document.getElementById('rate_bw_peak');

				label_scale   = document.getElementById('scale');
				label_scale_2 = document.getElementById('scale2');


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

					label_25.parentNode.appendChild(line);
					label_25.parentNode.appendChild(text);


					var line2 = G2.createElementNS('http://www.w3.org/2000/svg', 'line');
						line2.setAttribute('x1', i);
						line2.setAttribute('y1', 0);
						line2.setAttribute('x2', i);
						line2.setAttribute('y2', '100%');
						line2.setAttribute('style', 'stroke:black;stroke-width:0.1');

					var text2 = G2.createElementNS('http://www.w3.org/2000/svg', 'text');
						text2.setAttribute('x', i + 5);
						text2.setAttribute('y', 15);
						text2.setAttribute('style', 'fill:#999999; font-size:9pt');
						text2.appendChild(G.createTextNode(Math.round((width - i) / step / 60) + 'm'));

					label_25_2.parentNode.appendChild(line2);
					label_25_2.parentNode.appendChild(text2);
				}

				label_scale.innerHTML = String.format('<%:(%d minute window, %d second interval)%>', data_wanted / 60, 3);
				label_scale_2.innerHTML = String.format('<%:(%d minute window, %d second interval)%>', data_wanted / 60, 3);

				/* render datasets, start update interval */
				XHR.poll(3, '<%=build_url("admin/status/realtime/wireless_status", curdev)%>', null,
					function(x, data)
					{
						var noise_floor = 255;
						var rate_floor = 60000;

						for (var i = 0; i < data.length; i++) {
							noise_floor = Math.min(noise_floor, data[i][NOISE]);
							rate_floor = Math.min(rate_floor, data[i][RATE]);
						}

						noise_floor -= 5;

						var data_max   = 0;
						var data_scale = 0;
						var data_max_2   = 0;
						var data_scale_2 = 0;

						var data_rssi_avg = 0;
						var data_noise_avg = 0;
						var data_rate_avg = 0;

						var data_rssi_peak = 0;
						var data_noise_peak = 0;
						var data_rate_peak = 0;

						for (var i = data_stamp ? 0 : 1; i < data.length; i++)
						{
							/* skip overlapping entries */
							if (data[i][TIME] <= data_stamp)
								continue;

							data_rssi.push(data[i][RSSI] - noise_floor);
							data_noise.push(data[i][NOISE] - noise_floor);
							data_rate.push(Math.floor(data[i][RATE] / 1000));
						}

						/* cut off outdated entries */
						data_rssi = data_rssi.slice(data_rssi.length - data_wanted, data_rssi.length);
						data_noise = data_noise.slice(data_noise.length - data_wanted, data_noise.length);
						data_rate = data_rate.slice(data_rate.length - data_wanted, data_rate.length);

						/* find peak */
						for (var i = 0; i < data_rssi.length; i++)
						{
							data_max = Math.max(data_max, data_rssi[i]);
							data_max_2 = Math.max(data_max_2, data_rate[i]);

							data_rssi_peak = Math.max(data_rssi_peak, data_rssi[i]);
							data_noise_peak = Math.max(data_noise_peak, data_noise[i]);
							data_rate_peak = Math.max(data_rate_peak, data_rate[i]);

							if (i > 0)
							{
								data_rssi_avg = (data_rssi_avg + data_rssi[i]) / 2;
								data_noise_avg = (data_noise_avg + data_noise[i]) / 2;
								data_rate_avg = (data_rate_avg + data_rate[i]) / 2;
							}
							else
							{
								data_rssi_avg = data_rssi[i];
								data_noise_avg = data_noise[i];
								data_rate_avg = data_rate[i];
							}
						}

						/* remember current timestamp, calculate horizontal scale */
						data_stamp = data[data.length-1][TIME];
						data_scale = (height / (data_max * 1.1)).toFixed(1);
						data_scale_2 = (height / (data_max_2 * 1.1)).toFixed(1);

						/* plot data */
						var pt_rssi = '0,' + height;
						var pt_noise = '0,' + height;
						var pt_rate = '0,' + height;

						var y_rssi = 0;
						var y_noise = 0;
						var y_rate = 0;

						for (var i = 0; i < data_rssi.length; i++)
						{
							var x = i * step;

							y_rssi = height - Math.floor(data_rssi[i] * data_scale);
							y_noise = height - Math.floor(data_noise[i] * data_scale);
							y_rate = height - Math.floor(data_rate[i] * data_scale_2);

							y_rssi -= Math.floor(y_rssi % (1/data_scale));
							y_noise -= Math.floor(y_noise % (1/data_scale));

							pt_rssi += ' ' + x + ',' + y_rssi;
							pt_noise += ' ' + x + ',' + y_noise;
							pt_rate += ' ' + x + ',' + y_rate;
						}

						pt_rssi += ' ' + width + ',' + y_rssi + ' ' + width + ',' + height;
						pt_noise += ' ' + width + ',' + y_noise + ' ' + width + ',' + height;
						pt_rate += ' ' + width + ',' + y_rate + ' ' + width + ',' + height;

						line_rssi.setAttribute('points', pt_rssi);
						line_noise.setAttribute('points', pt_noise);
						line_rate.setAttribute('points', pt_rate);

						function wireless_label(dbm, noise)
						{
							if (noise)
								return String.format("%d <%:dBm%> (SNR %d <%:dBm%>)", noise_floor + dbm - 255, dbm - noise);
							else
								return String.format("%d <%:dBm%>", noise_floor + dbm - 255);
						}

						function rate_label(mbit)
						{
							return String.format("%d <%:Mbit/s%>", mbit);
						}

						label_25.firstChild.data = wireless_label(1.1 * 0.25 * data_max);
						label_50.firstChild.data = wireless_label(1.1 * 0.50 * data_max);
						label_75.firstChild.data = wireless_label(1.1 * 0.75 * data_max);

						label_25_2.firstChild.data = rate_label(1.1 * 0.25 * data_max_2);
						label_50_2.firstChild.data = rate_label(1.1 * 0.50 * data_max_2);
						label_75_2.firstChild.data = rate_label(1.1 * 0.75 * data_max_2);

						label_rssi_cur.innerHTML = wireless_label(data_rssi[data_rssi.length-1], data_noise[data_noise.length-1]).nobr();
						label_noise_cur.innerHTML = wireless_label(data_noise[data_noise.length-1]).nobr();

						label_rssi_avg.innerHTML = wireless_label(data_rssi_avg, data_noise_avg).nobr();
						label_noise_avg.innerHTML = wireless_label(data_noise_avg).nobr();

						label_rssi_peak.innerHTML = wireless_label(data_rssi_peak, data_noise_peak).nobr();
						label_noise_peak.innerHTML = wireless_label(data_noise_peak).nobr();

						label_rate_cur.innerHTML = rate_label(data_rate[data_rate.length-1]);
						label_rate_avg.innerHTML = rate_label(data_rate_avg);
						label_rate_peak.innerHTML = rate_label(data_rate_peak);
					}
				);
			}
		}, 1000
	);