void rec_k_short_qa(){
	ROOT::RDataFrame d("t", "candidates.root");
	auto dd = d
//      .Filter("centrality > 10.0")
			.Define( "candidate_pT", "std::vector<float> pT; for( auto mom : candidate_momenta ){ pT.push_back( mom.Pt() ); } return pT;")
			.Define("candidate_phi", "std::vector<float> phi; for( auto mom : candidate_momenta ){ phi.push_back( mom.Phi() ); } return phi;")
			.Define("candidate_rapidity", "std::vector<float> rapidity; for( auto mom : candidate_momenta ){ rapidity.push_back( mom.Rapidity() ); } return rapidity;")
			.Define("pT_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(0) ); } return err;")
			.Define("phi_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(1) ); } return err;")
			.Define("eta_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(2) ); } return err;")
			.Define("m_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(3) ); } return err;")
			.Define("daughter1_cos", "std::vector<float> cosine; for( int i=0; i<daughter_cosines.at(0).size(); ++i ){ cosine.push_back( daughter_cosines.at(0).at(i) ); } return cosine;")
			.Define("daughter2_cos", "std::vector<float> cosine; for( int i=0; i<daughter_cosines.at(1).size(); ++i ){ cosine.push_back( daughter_cosines.at(1).at(i) ); } return cosine;")
			.Define("daughter1_chi2_prim", "std::vector<float> chi2; for( int i=0; i<daughter_chi2_prim.at(0).size(); ++i ){ chi2.push_back( daughter_chi2_prim.at(0).at(i) ); } return chi2;")
			.Define("daughter2_chi2_prim", "std::vector<float> chi2; for( int i=0; i<daughter_chi2_prim.at(1).size(); ++i ){ chi2.push_back( daughter_chi2_prim.at(1).at(i) ); } return chi2;")
	//		.Define("candidate_chi2_geo_1", "std::vector<float> chi2; for( int i=0; i<chi2_geo.at(0).size(); ++i ){ chi2.push_back( chi2_geo.at(0).at(i) ); } return chi2;")
	//		.Define("candidate_chi2_topo", "std::vector<float> chi2; for( int i=0; i<chi2_topo.at(0).size(); ++i ){ chi2.push_back( chi2_topo.at(0).at(i) ); } return chi2;")
	//		.Define("candidate_cosine_topo", "std::vector<float> cosine; for( int i=0; i<cos_topo_.at(0).size(); ++i ){ cosine.push_back( cos_topo_.at(0).at(i) ); } return cosine;")
			.Define("good_candidate",
					"std::vector<int> good_candidate;"
					"for(int i=0; i<daughter_chi2_prim.at(0).size(); ++i){"
						"if( m_err.at(i)*2*candidate_mass.at(i) > 0.006 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( candidate_cos_topo.at(i) < 0.995 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
                                                "if( daughter2_cos.at(i) > 0.999 ){"
                                                        "good_candidate.push_back(0);"
                                                        "continue;"
                                                "}"
						"if( daughter1_chi2_prim.at(i) < 100 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( daughter2_chi2_prim.at(i) < 100 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( candidate_L.at(i) < 1 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( candidate_LdL.at(i) < 6.25 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( candidate_chi2_topo.at(i) > 40 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
                                                 "if( candidate_chi2_geo.at(i) > 20  ){"
                                                        "good_candidate.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter_dca.at(i) > 0.7  ){"
                                                        "good_candidate.push_back(0);"
                                                        "continue;"
                                                "}"
					
						"good_candidate.push_back( 1 );"
					"} return good_candidate;"
			)
         .Define("basic_cut",
                                        "std::vector<int> basic_cut;"
                                        "for(int i=0; i<daughter_chi2_prim.at(0).size(); ++i){"
                                               /* "if( m_err.at(i)*2*candidate_mass.at(i) > 0.001 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"*/
                                                "if( candidate_cos_topo.at(i) < 0.99 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"
                                               /* "if( daughter2_cos.at(i) < 0.99 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"*/
                                                "if( candidate_L.at(i) < 2.25 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( candidate_LdL.at(i) < 6.25 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"
                                                 "if( daughter_dca.at(i) > 0.728  ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"

                                                 

                                                "basic_cut.push_back( 1 );"
                                        "} return basic_cut;"
                        )
          .Define("basic_var",
                                        "std::vector<int> basic_var;"
                                        "for(int i=0; i<daughter_chi2_prim.at(0).size(); ++i){"
                                                "if( m_err.at(i)*2*candidate_mass.at(i) > 0.003 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter2_cos.at(i) < 0.99 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter1_chi2_prim.at(i) < 400 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter2_chi2_prim.at(i) < 20 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( candidate_L.at(i) < 2.25 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( candidate_LdL.at(i) < 6.25 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
						"if( candidate_cos_topo.at(i) < 0.999 || candidate_cos_topo.at(i)>0.9999  ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"

                                                "if( candidate_chi2_topo.at(i) > 100 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                 "if( candidate_chi2_geo.at(i) > 20  ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter_dca.at(i) > 0.728  ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"

                                                "basic_var.push_back( 1 );"
                                        "} return basic_var;"
                        )


			
	;

	std::vector<ROOT::RDF::RResultPtr<::TH1D>> hist1d;
	std::vector<ROOT::RDF::RResultPtr<::TH2D>> hist2d;
        std::vector<std::string> cuts {"good_candidate"};
	hist1d.push_back( dd.Histo1D( { "h1_mass", ";m (GeV/c^2); counts", 100, 0.4, 0.6 }, "candidate_mass" ) );
	hist1d.push_back( dd.Histo1D( { "h1_pT", ";p_{T} (GeV/c); counts", 100, 0.00, 2.0 }, "candidate_pT" ) );
	hist1d.push_back( dd.Histo1D( { "h1_phi", ";#varphi (rad); counts", 100, -3.50, 3.5 }, "candidate_phi" ) );
	hist1d.push_back( dd.Histo1D( { "h1_rapdity", ";y_{lab}; counts", 100, 0.0, 3.5 }, "candidate_rapidity" ) );
	hist1d.push_back( dd.Histo1D( { "h1_pT_err", ";#Deltap_{T}; counts", 100, 0.0, 0.1 }, "pT_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_phi_err", ";#Delta#varphi; counts", 100, 0.0, 0.1 }, "phi_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_eta_err", ";#Delta#eta; counts", 100, 0.0, 0.1 }, "eta_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_mass_err", ";#Deltam; counts", 100, 0.0, 0.05 }, "m_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter1_cos", ";cos(#varphi_{1}); counts", 100, 0.8, 1.0 }, "daughter1_cos" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter2_cos", ";cos(#varphi_{2}); counts", 100, 0.98, 1.0 }, "daughter2_cos" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter1_chi2_prim", ";#chi^{2}_{prim}^{1}; counts", 500, 0.0, 1000.0 }, "daughter1_chi2_prim" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter2_chi2_prim", ";#chi^{2}_{prim}^{2}; counts", 150, 0.0, 300.0 }, "daughter2_chi2_prim" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_chi2_geo", ";#chi^{2}_{geo}; counts", 500, 0.0, 100.0 }, "candidate_chi2_geo" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_chi2_topo", ";#chi^{2}_{topo}; counts", 150, 0.0, 150.0 }, "candidate_chi2_topo" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_cos_topo", ";r_{#lambda}p_{#lambda}; counts", 100, 0.98, 1.0 }, "candidate_cos_topo" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter_dca", ";DCA; counts", 200, 0.0, 1 }, "daughter_dca" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter_distance_to_sv", ";DCA_{prim}; counts", 100, 0.0, 10.0 }, "distance_to_sv" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_L", ";L; counts", 100, 0.0, 20.0 }, "candidate_L" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_LdL", ";L/dL; counts", 100, 0.0, 20.0 }, "candidate_LdL" ) );
	hist2d.push_back( dd.Histo2D( { "h2_pT_y", ";y;p_{T} (GeV/c)", 30, 0.0, 3.0, 25, 0.0, 2.5  }, "candidate_rapidity", "candidate_pT" ) );
       
 hist2d.push_back( dd.Histo2D( { "h2_m_err_m_inv", ";#Deltam (GeV/c^2);m_inv (GeV/c^2)", 100, 0.0, 0.01, 100, 0.4, 0.6  }, "m_err", "candidate_mass" ) );
 hist2d.push_back( dd.Histo2D( { "h2_pi_chi2_prim_m_inv", ";#chi^{2}_{prim}^{1};m_inv (GeV/c^2)", 100, 0.0, 300, 100, 0.4, 0.6  }, "daughter1_chi2_prim", "candidate_mass" ) );       
 hist2d.push_back( dd.Histo2D( { "h2_chi2_topo_m_inv", ";#chi^{2}_{topo};m_inv (GeV/c^2)", 100, 0.0, 100, 100, 0.4, 0.6  }, "candidate_chi2_topo", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_p_chi2_prim_m_inv", ";#chi^{2}_{prim}^{2};m_inv (GeV/c^2)", 100, 0.0, 100, 100, 0.4, 0.6  }, "daughter2_chi2_prim", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_p_lam_m_inv", ";cos(#varphi_{2});m_inv (GeV/c^2)", 100, 0.98, 1, 100, 0.4, 0.6  }, "daughter2_cos", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_dca_m_inv", ";DCA;m_inv (GeV/c^2)", 200, 0.0, 2, 100, 0.4, 0.6  }, "daughter_dca", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_chi2_geo_m_inv", ";#chi^{2}_{geo};m_inv (GeV/c^2)", 50, 0.0, 100, 100, 0.4, 0.6  }, "candidate_chi2_geo", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_L_m_inv", ";L;m_inv (GeV/c^2)", 80, 0.0, 20, 100, 0.4, 0.6  }, "candidate_L", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_m_inv", ";L/dL;m_inv (GeV/c^2)", 160, 0.0, 40, 100, 0.4, 0.6  }, "candidate_LdL", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_m_inv", ";r_{#lambda}p_{#lambda};m_inv (GeV/c^2)", 100, 0.98, 1, 100, 0.4, 0.6  }, "candidate_cos_topo", "candidate_mass" ) );

 hist2d.push_back( dd.Histo2D( { "h2_chi2_topo_pi_chi2", ";#chi^{2}_{topo};#chi^{2}_{prim}^{1}", 100, 0.0, 100, 100, 0, 1000  }, "candidate_chi2_topo", "daughter1_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_p_chi2_prim_pi_chi2", ";#chi^{2}_{prim}^{2};#chi^{2}_{prim}^{1}", 100, 0.0, 200, 100, 0, 1000  }, "daughter2_chi2_prim", "daughter1_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_p_lam_pi_chi2", ";cos(#varphi_{2});#chi^{2}_{prim}^{1}", 100, 0.98, 1, 100, 0, 1000   }, "daughter2_cos", "daughter1_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_dca_pi_chi2", ";DCA;#chi^{2}_{prim}^{1}", 200, 0.0, 2, 100, 0, 1000   }, "daughter_dca", "daughter1_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_chi2_geo_pi_chi2", ";#chi^{2}_{geo};#chi^{2}_{prim}^{1}", 50, 0.0, 100, 100, 0, 1000   }, "candidate_chi2_geo", "daughter1_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_L_pi_chi2", ";L;#chi^{2}_{prim}^{1}", 80, 0.0, 20, 100, 0, 1000   }, "candidate_L", "daughter1_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_pi_chi2", ";L/dL;#chi^{2}_{prim}^{1}", 160, 0.0, 40, 100, 0, 1000   }, "candidate_LdL", "daughter1_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_pi_chi2", ";r_{#lambda}p_{#lambda};#chi^{2}_{prim}^{1}", 100, 0.98, 1, 100, 0, 1000   }, "candidate_cos_topo", "daughter1_chi2_prim" ) );

hist2d.push_back( dd.Histo2D( { "h2_p_chi2_prim_chi2_topo", ";#chi^{2}_{prim}^{2};#chi^{2}_{topo}", 100, 0.0, 200, 100, 0, 100  }, "daughter2_chi2_prim", "candidate_chi2_topo" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_p_lam_chi2_topo", ";cos(#varphi_{2});#chi^{2}_{topo}", 100, 0.98, 1, 100, 0, 100   }, "daughter2_cos", "candidate_chi2_topo" ) );
hist2d.push_back( dd.Histo2D( { "h2_dca_chi2_topo", ";DCA;#chi^{2}_{topo}", 200, 0.0, 2, 100, 0, 100   }, "daughter_dca", "candidate_chi2_topo" ) );
hist2d.push_back( dd.Histo2D( { "h2_chi2_geo_chi2_topo", ";#chi^{2}_{geo};#chi^{2}_{topo}", 50, 0.0, 100, 100, 0, 100   }, "candidate_chi2_geo", "candidate_chi2_topo" ) );
hist2d.push_back( dd.Histo2D( { "h2_L_chi2_topo", ";L;#chi^{2}_{topo}", 80, 0.0, 20, 100, 0, 100   }, "candidate_L", "candidate_chi2_topo" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_chi2_topo", ";L/dL;#chi^{2}_{topo}", 160, 0.0, 40, 100, 0, 100   }, "candidate_LdL", "candidate_chi2_topo" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_chi2_topo", ";r_{#lambda}p_{#lambda};#chi^{2}_{topo}", 100, 0.98, 1, 100, 0, 100   }, "candidate_cos_topo", "candidate_chi2_topo" ) );


hist2d.push_back( dd.Histo2D( { "h2_cos_p_lam_p_chi2", ";cos(#varphi_{2});#chi^{2}_{prim}^{2}", 100, 0.98, 1, 100, 0, 200   }, "daughter2_cos", "daughter2_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_dca_p_chi2", ";DCA;#chi^{2}_{prim}^{2}", 200, 0.0, 2, 100, 0, 200   }, "daughter_dca", "daughter2_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_chi2_geo_p_chi2", ";#chi^{2}_{geo};#chi^{2}_{prim}^{2}", 50, 0.0, 100, 100, 0, 200   }, "candidate_chi2_geo", "daughter2_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_L_p_chi2", ";L;#chi^{2}_{prim}^{2}", 80, 0.0, 20, 100, 0, 200   }, "candidate_L", "daughter2_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_p_chi2", ";L/dL;#chi^{2}_{prim}^{2}", 160, 0.0, 40, 100, 0, 200   }, "candidate_LdL", "daughter2_chi2_prim" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_p_chi2", ";r_{#lambda}p_{#lambda};#chi^{2}_{prim}^{2}", 100, 0.98, 1, 100, 0, 200   }, "candidate_cos_topo", "daughter2_chi2_prim" ) );

hist2d.push_back( dd.Histo2D( { "h2_dca_cos_p_lam", ";DCA;cos(#varphi_{2})", 200, 0.0, 2, 100, 0.98, 1   }, "daughter_dca", "daughter2_cos" ) );
hist2d.push_back( dd.Histo2D( { "h2_chi2_geo_cos_p_lam", ";#chi^{2}_{geo};cos(#varphi_{2})", 50, 0.0, 100, 100, 0.98, 1    }, "candidate_chi2_geo", "daughter2_cos" ) );
hist2d.push_back( dd.Histo2D( { "h2_L_cos_p_lam", ";L;cos(#varphi_{2})", 80, 0.0, 20, 100, 0.98, 1    }, "candidate_L", "daughter2_cos" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_cos_p_lam", ";L/dL;cos(#varphi_{2})", 160, 0.0, 40, 100, 0.98, 1    }, "candidate_LdL", "daughter2_cos" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_cos_p_lam", ";r_{#lambda}p_{#lambda};cos(#varphi_{2})", 100, 0.98, 1, 100, 0.98, 1    }, "candidate_cos_topo", "daughter2_cos" ) );

hist2d.push_back( dd.Histo2D( { "h2_chi2_geo_dca", ";#chi^{2}_{geo};DCA", 50, 0.0, 100, 200, 0, 2    }, "candidate_chi2_geo", "daughter_dca" ) );
hist2d.push_back( dd.Histo2D( { "h2_L_dca", ";L;DCA", 80, 0.0, 20, 200, 0, 2    }, "candidate_L", "daughter_dca" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_dca", ";L/dL;DCA", 160, 0.0, 40, 200, 0, 2    }, "candidate_LdL", "daughter_dca" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_dca", ";r_{#lambda}p_{#lambda};DCA", 100, 0.98, 1, 200, 0, 2    }, "candidate_cos_topo", "daughter_dca" ) );

hist2d.push_back( dd.Histo2D( { "h2_L_chi2_geo", ";L;#chi^{2}_{geo}", 80, 0.0, 20, 50, 0, 100    }, "candidate_L", "candidate_chi2_geo" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_chi2_geo", ";L/dL;#chi^{2}_{geo}", 160, 0.0, 40, 50, 0, 100    }, "candidate_LdL", "candidate_chi2_geo" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_chi2_geo", ";r_{#lambda}p_{#lambda};#chi^{2}_{geo}", 100, 0.98, 1, 50, 0, 100    }, "candidate_cos_topo", "candidate_chi2_geo" ) );

hist2d.push_back( dd.Histo2D( { "h2_LdL_L", ";L/dL;L", 160, 0.0, 40, 80, 0, 20    }, "candidate_LdL", "candidate_L" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_L", ";r_{#lambda}p_{#lambda};L", 100, 0.98, 1, 80, 0, 20    }, "candidate_cos_topo", "candidate_L" ) );

hist2d.push_back( dd.Histo2D( { "h2_cos_topo_LdL", ";r_{#lambda}p_{#lambda};L/dL", 100, 0.98, 1, 160, 0, 40    }, "candidate_cos_topo", "candidate_LdL" ) );


	for( auto cut : cuts ){
		hist1d.push_back( dd.Histo1D( { std::data("h1_mass_"+cut), ";m (GeV/c^2); counts", 100, 0.4, 0.6 }, "candidate_mass", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_pT_"+cut), ";p_{T} (GeV/c); counts", 100, 0.00, 2.0 }, "candidate_pT", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_phi_"+cut), ";#varphi (rad); counts", 100, -3.50, 3.5 }, "candidate_phi", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_rapdity_"+cut), ";y_{lab}; counts", 100, 0.0, 3.5 }, "candidate_rapidity", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_pT_err_"+cut), ";#Deltap_{T}; counts", 100, 0.0, 0.1 }, "pT_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_phi_err_"+cut), ";#Delta#varphi; counts", 100, 0.0, 0.1 }, "phi_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_eta_err_"+cut), ";#Delta#eta; counts", 100, 0.0, 0.1 }, "eta_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_mass_err_"+cut), ";#Deltam; counts", 100, 0.0, 0.05 }, "m_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter1_cos_"+cut), ";cos(#varphi_{1}); counts", 100, 0.8, 1.0 }, "daughter1_cos", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter2_cos_"+cut), ";cos(#varphi_{2}); counts", 100, 0.98, 1.0 }, "daughter2_cos", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter1_chi2_prim_"+cut), ";#chi^{2}_{prim}^{1}; counts", 500, 0.0, 1000.0 }, "daughter1_chi2_prim", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter2_chi2_prim_"+cut), ";#chi^{2}_{prim}^{2}; counts", 150, 0.0, 300.0 }, "daughter2_chi2_prim", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_chi2_geo_"+cut), ";#chi^{2}_{geo}; counts", 500, 0.0, 100.0 }, "candidate_chi2_geo", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_chi2_topo_"+cut), ";#chi^{2}_{topo}; counts", 150, 0.0, 150.0 }, "candidate_chi2_topo", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_cos_topo_"+cut), ";r_{#lambda}p_{#lambda}; counts", 100, 0.98, 1.0 }, "candidate_cos_topo", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter_dca_"+cut), ";DCA; counts", 100, 0.0, 1 }, "daughter_dca", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter_distance_to_sv_"+cut), ";DCA_{prim}; counts", 100, 0.0, 10.0 }, "distance_to_sv", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_L_"+cut), ";L; counts", 100, 0.0, 20.0 }, "candidate_L", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_LdL_"+cut), ";L/dL; counts", 100, 0.0, 20.0 }, "candidate_LdL", cut ) );
			hist2d.push_back( dd.Histo2D( { std::data("h2_pT_y_"+cut), ";y;p_{T} (GeV/c)", 30, 0.0, 3.0, 25, 0.0, 2.5  }, "candidate_rapidity", "candidate_pT", cut ) );

hist2d.push_back( dd.Histo2D( { std::data("h2_m_err_m_inv"+cut), ";#Deltam (GeV/c^2);m_inv (GeV/c^2)", 100, 0.0, 0.01, 100, 0.4, 0.6  }, "m_err", "candidate_mass",cut ) );
 hist2d.push_back( dd.Histo2D( { std::data("h2_pi_chi2_prim_m_inv"+cut), ";#chi^{2}_{prim}^{1};m_inv (GeV/c^2)", 1000, 0, 10000, 100, 0.4, 0.6  }, "daughter1_chi2_prim", "candidate_mass",cut ) );       
 hist2d.push_back( dd.Histo2D( { std::data("h2_chi2_topo_m_inv"+cut), ";#chi^{2}_{topo};m_inv (GeV/c^2)", 200, 0.0, 200, 100, 0.4, 0.6  }, "candidate_chi2_topo", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_p_chi2_prim_m_inv"+cut), ";#chi^{2}_{prim}^{2};m_inv (GeV/c^2)", 1000, 0, 1000, 100, 0.4, 0.6  }, "daughter2_chi2_prim", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_cos_pi_p_lam_m_inv"+cut), ";cos(#varphi_{2});m_inv (GeV/c^2)", 1000, 0.99, 1, 100, 0.4, 0.6  }, "daughter2_cos", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_cos_pi_n_lam_m_inv"+cut), ";cos(#varphi_{1});m_inv (GeV/c^2)", 1000, 0.99, 1, 100, 0.4, 0.6  }, "daughter1_cos", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_dca_m_inv"+cut), ";DCA;m_inv (GeV/c^2)", 200, 0.0, 2, 100, 0.4, 0.6  }, "daughter_dca", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_chi2_geo_m_inv"+cut), ";#chi^{2}_{geo};m_inv (GeV/c^2)", 100, 0.0, 100, 100, 0.4, 0.6  }, "candidate_chi2_geo", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_L_m_inv"+cut), ";L;m_inv (GeV/c^2)", 100, 0.0, 50, 100, 0.4, 0.6  }, "candidate_L", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_LdL_m_inv"+cut), ";L/dL;m_inv (GeV/c^2)", 200, 0.0, 100, 100, 0.4, 0.6  }, "candidate_LdL", "candidate_mass",cut ) );
hist2d.push_back( dd.Histo2D( { std::data("h2_cos_topo_m_inv"+cut), ";r_{#lambda}p_{#lambda};m_inv (GeV/c^2)", 1000, 0.99, 1, 100, 0.4, 0.6  }, "candidate_cos_topo", "candidate_mass",cut ) );

	}
	auto file_out = TFile::Open("rec_k_short_qa.root", "recreate");
	for( auto& h1 : hist1d )
		h1->Write();
	for( auto& h2 : hist2d )
		h2->Write();
	file_out->Close();
}
